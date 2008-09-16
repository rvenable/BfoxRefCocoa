<?php
	define('BFOX_UNIQUE_ID_PART_SIZE', 8);
	define('BFOX_UNIQUE_ID_MASK', 0xFF);

	function bfox_get_book_name($book_id)
	{
		global $wpdb;
		$query = $wpdb->prepare("SELECT name FROM " . BFOX_BOOKS_TABLE . " WHERE id = %d", $book_id);
		return $wpdb->get_var($query);
	}

	function bfox_find_book_id($synonym)
	{
		global $wpdb;
		$query = $wpdb->prepare("SELECT book_id FROM " . BFOX_SYNONYMS_TABLE . " WHERE synonym LIKE %s", trim($synonym));
		if (isset($query))
			return $wpdb->get_var($query);
		return false;
	}

	/*
	 This class is used to represent a bible reference using the following integer values:
	 book_id, chapter1, verse1, chapter2, verse2
	 
	 This form allows easy conversion between the unique ID form (BibleRefSingle) and string input/output
	 */
	class BibleRefParsed
	{
		function set($book_id = 0, $chapter1 = 0, $verse1 = 0, $chapter2 = 0, $verse2 = 0)
		{
			$book_id  &= BFOX_UNIQUE_ID_MASK;
			$chapter1 &= BFOX_UNIQUE_ID_MASK;
			$verse1   &= BFOX_UNIQUE_ID_MASK;
			$chapter2 &= BFOX_UNIQUE_ID_MASK;
			$verse2   &= BFOX_UNIQUE_ID_MASK;

			if (0 < $book_id) $this->book_id = $book_id;
			if (0 < $chapter1) $this->chapter1 = $chapter1;
			if (0 < $verse1) $this->verse1 = $verse1;
			if (0 < $chapter2) $this->chapter2 = $chapter2;
			if (0 < $verse2) $this->verse2 = $verse2;
		}

		function set_by_unique_ids($unique_ids)
		{
			$book_id  = (int) (($unique_ids[0] >> (BFOX_UNIQUE_ID_PART_SIZE * 2)) & BFOX_UNIQUE_ID_MASK);
			$chapter1 = (int) (($unique_ids[0] >> BFOX_UNIQUE_ID_PART_SIZE) & BFOX_UNIQUE_ID_MASK);
			$verse1   = (int)  ($unique_ids[0] & BFOX_UNIQUE_ID_MASK);
			$chapter2 = (int) (($unique_ids[1] >> BFOX_UNIQUE_ID_PART_SIZE) & BFOX_UNIQUE_ID_MASK);
			$verse2   = (int)  ($unique_ids[1] & BFOX_UNIQUE_ID_MASK);

			// If chapter two is set to max, we should not use it
			if ((BFOX_UNIQUE_ID_MASK == $chapter2) || ($chapter1 == $chapter2))
				$chapter2 = 0;
			if ((BFOX_UNIQUE_ID_MASK == $verse2) || ($verse1 == $verse2))
				$verse2 = 0;

			$this->set($book_id, $chapter1, $verse1, $chapter2, $verse1);
		}
		
		function set_by_string($str)
		{
			// Convert all whitespace to single spaces
			$str = preg_replace('/\s+/', ' ', $str);
			
			// Find the last dash in the string and use it to divide the ref
			$dash_left = trim($str);
			if ($pos = strrpos($dash_left, '-'))
			{
				$dash_right = trim(substr($dash_left, $pos + 1));
				$dash_left = trim(substr($dash_left, 0, $pos));
			}
			
			// Parse the left side of the dash
			$left_colon_list = explode(':', $dash_left);
			$left_colon_count = count($left_colon_list);
			
			// We can only have one dash
			if (2 >= $left_colon_count)
			{
				// If there was a dash, then save the right side as an integer verse number
				if (1 < $left_colon_count)
					$verse_num = (int) trim($left_colon_list[1]);
				
				// If we didn't have any problems with the right side of the colon (verse_num)
				if ((!isset($verse_num)) || (0 < $verse_num))
				{
					if (isset($verse_num)) $verse1 = $verse_num;
					
					// Parse the left side of the colon to get the book name and the chapter num
					$colon_left = trim($left_colon_list[0]);
					if ($pos = strrpos($colon_left, ' '))
					{
						// Get the chapter number which must be greater than 0
						$chapter_num = (int) trim(substr($colon_left, $pos + 1));
						if (0 < $chapter_num)
						{
							$chapter1 = $chapter_num;
							$book_str = trim(substr($colon_left, 0, $pos));
						}
					}
				}
			}
			
			// Parse the right side of the dash if the left side worked (yielding at least a chapter id)
			if ((isset($dash_right)) && (isset($chapter1)))
			{
				$right_colon_list = explode(':', $dash_right);
				$right_colon_count = count($right_colon_list);
				
				// We can only have one dash
				if (2 >= $right_colon_count)
				{
					// If there was a dash, then save the right side as an integer
					if (1 < $right_colon_count)
						$num2 = (int) trim($right_colon_list[1]);
					
					// If we didn't have any problems with the right side of the colon (num2)
					// Then save the left side as an integer
					if ((!isset($num2)) || (0 < $num2))
						$num1 = (int) trim($right_colon_list[0]);
				}
				
				// If we got at least one integer and it is greater than zero,
				// then everything went fine on this side of the dash
				if ((isset($num1)) && (0 < $num1))
				{
					if (isset($num2))
					{
						// If we have 2 numbers then the first is a chapter and the second is a verse
						$chapter2 = $num1;
						$verse2 = $num2;
					}
					else
					{
						// If there is only one number on the right side of the dash,
						// then it can be either a chapter or a verse
						
						// If the left side of the dash yielded a verse2,
						// then we must have a verse on the right side of the dash also
						if (isset($verse1)) $verse2 = $num1;
						else $chapter2 = $num1;
					}
				}
				else
				{
					// If we didn't get any numbers on this side of the dash
					// then the string is misformatted
					unset($chapter1);
				}
			}
			
			// If we haven't set a book string yet, set it to the original str
			if (!isset($book_str)) $book_str = $str;
			
			// Try to find a book id for the book string
			if ($book_id = bfox_find_book_id(trim($book_str)))
			{
				// If we found a book id, this must be a valid bible reference string
				$this->set($book_id, $chapter1, $verse1, $chapter2, $verse2);
			}
		}
		
		function get_unique_ids()
		{
			// Create the unique ids
			$unique_ids = array();

			if (isset($this->book_id))
			{
				/*
				 Conversion methods:
				 john			0:0-max:max		max:max
				 john 1			1:0-1:max		ch1:max
				 john 1-2		1:0-2:max		ch2:max
				 john 1:1		1:1-1:1			ch1:vs1
				 john 1:1-5		1:1-5:max		ch2:max
				 john 1:1-0:2	1:1-1:2			ch1:vs2
				 john 1:1-5:2	1:1-5:2			ch2:vs2
				 john 1-5:2		1:0-5:2			ch2:vs2
				 
				 When chapter2 is not set (== 0): chapter2 equals chapter1 unless chapter1 is not set
				 When verse2 is not set (== 0): verse2 equals max unless chapter2 is not set and verse1 is set
				 */
				
				if (isset($this->chapter1)) $chapter1 = $this->chapter1;
				else $chapter1 = 0;

				if (isset($this->verse1)) $verse1 = $this->verse1;
				else $verse1 = 0;
				
				// When verse2 is not set: verse2 equals max unless chapter2 is not set and verse1 is set
				if (isset($this->verse2)) $verse2 = $this->verse2;
				else $verse2 = ((isset($this->verse1)) && (!isset($this->chapter2))) ? $verse1 : BFOX_UNIQUE_ID_MASK;

				// When chapter2 is not set: chapter2 equals chapter1 unless chapter1 is not set
				if (isset($this->chapter2)) $chapter2 = $this->chapter2;
				else $chapter2 = (isset($this->chapter1)) ? $chapter1 : BFOX_UNIQUE_ID_MASK;
				
				// Set the unique IDs according to the book IDs
				$unique_ids[0] = $unique_ids[1] = $this->book_id << (BFOX_UNIQUE_ID_PART_SIZE * 2);

				// Add the verse and chapter information to the unique ids
				$unique_ids[0] += ($chapter1 << BFOX_UNIQUE_ID_PART_SIZE) + $verse1;
				$unique_ids[1] += ($chapter2 << BFOX_UNIQUE_ID_PART_SIZE) + $verse2;
			}

			return $unique_ids;
		}

		function get_string()
		{
			if (isset($this->str))
				return $this->str;
			
			if (!isset($this->book_name))
				$this->book_name = bfox_get_book_name($this->book_id);
			
			// Create the reference string
			$str = "$this->book_name";
			if (isset($this->chapter1))
			{
				$str .= " {$this->chapter1}";
				if (isset($this->verse1))
					$str .= ":{$this->verse1}";
				if (isset($this->chapter2))
				{
					$str .= "-{$this->chapter2}";
					if (isset($this->verse2))
						$str .= ":{$this->verse2}";
				}
				else if (isset($this->verse2))
					$str .= "-{$this->verse2}";
			}
			
			$this->str = $str;
			return $this->str;
		}

		// Increments the parsed bible reference
		function increment($factor = 1)
		{
			// NOTE: Currently the function only considers how many chapters are in the ref
			// It will need to consider how many verses as well
			// Also, it doesn't currently handle moving on to the next book of the bible

			// Calculate how much we should increment our chapter numbers
			$chapDiff = $this->chapter2 - $this->chapter1;
			$chapInc = 1;
			if (0 < $chapDiff) $chapInc = $chapDiff;
			$chapInc *= $factor;

			// Increment the chapters
			if (isset($this->chapter1)) $this->chapter1 += $chapInc;
			if (isset($this->chapter2)) $this->chapter2 += $chapInc;
		}
	}

	/*
	 This class is used to represent a bible reference as two unique IDs
	 */
	class BibleRefSingle
	{
		private $unique_ids = array(0, 0);

		function get_unique_ids()
		{
			return $this->unique_ids;
		}

		function get_string()
		{
			return $this->get_parsed()->get_string();
		}

		// Returns the parsed array form of the bible reference
		function get_parsed()
		{
			if (isset($this->parsed))
				return $this->parsed;

			$this->parsed = new BibleRefParsed;
			$this->parsed->set_by_unique_ids($this->unique_ids);
			return $this->parsed;
		}

		function set_by_unique_ids($unique_ids)
		{
			// The unique ids are valid only if the first is greater than 0 and the second is greater than (or equal to) the first
			if ((0 < $unique_ids[0]) && ($unique_ids[0] <= $unique_ids[1]))
			{
				$this->unique_ids = $unique_ids;
				return true;
			}
			return false;
		}

		function set_by_parsed(BibleRefParsed $parsed)
		{
			$this->parsed = $parsed;
			return $this->set_by_unique_ids($this->parsed->get_unique_ids());
		}
		
		function set_by_string($str)
		{
			$parsed = new BibleRefParsed;
			$parsed->set_by_string($str);
			return $this->set_by_parsed($parsed);
		}

		// Returns an SQL expression for comparing this bible reference against one unique id column
		function sql_where($col1 = 'unique_id')
		{
			global $wpdb;
			return $wpdb->prepare("($col1 >= %d AND $col1 <= %d)", $this->unique_ids[0], $this->unique_ids[1]);
		}

		// Returns an SQL expression for comparing this bible reference against two unique id columns
		function sql_where2($col1, $col2)
		{
			/*
			 Equation for determining whether one bible reference overlaps another
			 
			 a1 <= b1 and b1 <= a2 or
			 a1 <= b2 and b2 <= a2
			 or
			 b1 <= a1 and a1 <= b2 or
			 b1 <= a2 and a2 <= b2
			 
			 a1b1 * b1a2 + a1b2 * b2a2 + b1a1 * a1b2 + b1a2 * a2b2
			 b1a2 * (a1b1 + a2b2) + a1b2 * (b1a1 + b2a2)
			 
			 */
			
			global $wpdb;
			return $wpdb->prepare("((($col1 <= %d) AND ((%d <= $col1) OR (%d <= $col2))) OR
								    ((%d <= $col2) AND (($col1 <= %d) OR ($col2 <= %d))))",
								  $this->unique_ids[1], $this->unique_ids[0], $this->unique_ids[1],
								  $this->unique_ids[0], $this->unique_ids[0], $this->unique_ids[1]);
		}

		function increment($factor = 1)
		{
			$parsed = $this->get_parsed();
			$parsed->increment($factor);
			return $this->set_by_parsed($parsed);
		}
	}

	/*
	 This class is a wrapper aroung BibleRefSingle to store it in an array
	 */
	class BibleRefs
	{
		private $refs = array();

		// Returns the internal array of BibleRefSingles converted to an
		// array of BibleRefs where each element has just one BibleRefSingle
		function get_refs_array()
		{
			$refs_array = array();
			foreach ($this->refs as $ref)
			{
				$new_ref = new BibleRefs;
				$new_ref->push_ref_single($ref);
				$refs_array[] = $new_ref;
			}
			return $refs_array;
		}
		
		function get_sets()
		{
			$unique_id_sets = array();
			foreach ($this->refs as $ref) $unique_id_sets[] = $ref->get_unique_ids();
			return $unique_id_sets;
		}

		function get_string()
		{
			$strs = array();
			foreach ($this->refs as $ref) $strs[] = $ref->get_string();
			return implode('; ', $strs);
		}

		function get_count()
		{
			return count($this->refs);
		}

		function push_ref_single(BibleRefSingle $ref)
		{
			$this->refs[] = $ref;
		}

		function push_sets($unique_id_sets)
		{
			$count = 0;
			foreach ($unique_id_sets as $unique_ids)
			{
				$ref = new BibleRefSingle;
				if ($ref->set_by_unique_ids($unique_ids))
				{
					$this->refs[] = $ref;
					$count++;
				}
			}
			return $count;
		}

		function push_string($str)
		{
			$count = 0;
			$refstrs = preg_split("/[\n,;]/", trim($str));
			foreach ($refstrs as $refstr)
			{
				$ref = new BibleRefSingle;
				if ($ref->set_by_string($refstr))
				{
					$this->refs[] = $ref;
					$count++;
				}
			}
			return $count;
		}

		function sql_where($col1 = 'unique_id')
		{
			$strs = array();
			foreach ($this->refs as $ref) $strs[] = $ref->sql_where($col1);
			return '(' . implode(' OR ', $strs) . ')';
		}

		function sql_where2($col1, $col2)
		{
			$strs = array();
			foreach ($this->refs as $ref) $strs[] = $ref->sql_where2($col1, $col2);
			return '(' . implode(' OR ', $strs) . ')';
		}

		function increment($factor = 1)
		{
			foreach ($this->refs as &$ref) $ref->increment($factor);
		}
	}

?>