<?php

	function bfox_edit_plan_menu($plan = NULL)
	{
		if (!is_null($plan))
		{
			global $bfox_plan;
			$title = $plan->name;
			$summary = $plan->summary;
			$text = $bfox_plan->get_plan_text($plan->id);
			$section_size = $plan->frequency;
			$plan_id = $plan->id;
			$header = 'Edit Reading Plan';
			$action_str = 'Edit';
			$text_box_info = 'Edit the sections in your plan. <br/> Each line is a different section of your reading plan.';
		}
		else
		{
			$header = 'Create a Reading Plan';
			$action_str = 'Create';
			$text_box_info = 'Which passages of the bible would you like to read? <br/> Type the passages below: ';
		}
	?>
<h2><?php echo $header; ?></h2>
<form action="admin.php" method="get">
<input type="hidden" name="page" value="<?php echo BFOX_PLAN_SUBPAGE; ?>">
<input type="hidden" name="hidden_field" value="Y">
<input type="hidden" name="plan_id" value="<?php echo $plan_id; ?>">
Title: <input type="text" size="20" maxlength="128" name="plan_name" value="<?php echo $title; ?>"> <br/>
Summary: <input type="text" size="20" maxlength="128" name="plan_summary" value="<?php echo $summary; ?>"> <br/> <br/>
<?php echo $text_box_info; ?><br/>
<textarea rows="5" cols="40" wrap="physical" name="books"><?php echo $text; ?></textarea><br/> <br/>
How fast will you read this plan?<br/>
<input type="text" size="10" maxlength="40" name="num_chapters" value="<?php echo $section_size; ?>"> chapters per period <br/> <br/>
<input type="submit" value="<?php echo $action_str; ?> Plan" class="button" />
</form>
<?php
	}

	function bfox_plan_schedule_menu()
	{
		$header = 'Schedule';
	?>
<h2><?php echo $header; ?></h2>
<form action="admin.php" method="get">
How many readings at a time?<br/>
<input type="text" size="10" maxlength="40" name="num_chapters" value="<?php echo $section_size; ?>"> readings at at time.<br/><br/>
How often will you be reading this plan?<br/>
<table>

<tr>
<td><input type="radio" name="frequency" value="day"></td>
<td>Daily</td>
<td>
<table width="100%">
<tr><td colspan="7">Which days of the week?</td><tr>
<tr>
<td><input type="checkbox" name="dayofweek" value="1">Sun</td>
<td><input type="checkbox" name="dayofweek" value="2">Mon</td>
<td><input type="checkbox" name="dayofweek" value="3">Tue</td>
<td><input type="checkbox" name="dayofweek" value="4">Wed</td>
<td><input type="checkbox" name="dayofweek" value="5">Thu</td>
<td><input type="checkbox" name="dayofweek" value="6">Fri</td>
<td><input type="checkbox" name="dayofweek" value="7">Sat</td>
</tr>
</table>
</td>
</tr>

<tr>
<td><input type="radio" name="frequency" value="week"></td>
<td>Weekly</td>
<td>
<table width="100%">
<tr><td colspan="7">Which day of the week?</td><tr>
<tr>
<td><input type="radio" name="dayofweek" value="1">Sun</td>
<td><input type="radio" name="dayofweek" value="2">Mon</td>
<td><input type="radio" name="dayofweek" value="3">Tue</td>
<td><input type="radio" name="dayofweek" value="4">Wed</td>
<td><input type="radio" name="dayofweek" value="5">Thu</td>
<td><input type="radio" name="dayofweek" value="6">Fri</td>
<td><input type="radio" name="dayofweek" value="7">Sat</td>
</tr>
</table>
</td>
</tr>

<tr>
<td><input type="radio" name="frequency" value="month"></td>
<td>Monthly</td>
<td>
<table width="100%">
<tr><td>Which days of the month?</td><tr>
<tr><td><input type="text" size="40" maxlength="40" name="num_chapters" value=""></td></tr>
</table>
</td>
</tr>
</table>

<input type="submit" value="<?php echo $action_str; ?> Plan" class="button" />
</form>
<?php
	}

	function bfox_echo_plan($plan, $num_cols = 3, $skip_read = false)
	{
		// Divide the plan into 3 columns
		$originals = bfox_divide_into_cols($plan->refs, $num_cols, 5);

		$headers = '<th width="1*"></th><th width="10*">Passage</th>';
		if (isset($plan->dates))
		{
			$headers .= '<th width="5*">Date</th>';
		}

		if (isset($plan_list->unread) || isset($plan_list->read))
		{
			$headers .= '<th width="5*">My Progress</th>';
		}

		$content = '';
		$unread_count = 0;
		$content .= '<table width="100%"><tr>';
		foreach ($originals as $original_array)
		{
			$content .= '<td valign="top"><table width="100%" style="text-align:left"><tr>' . $headers . '</tr>';
			foreach ($original_array as $period_id => $original)
			{
				if (isset($plan->current_reading) && ($period_id == $plan->current_reading))
				{
					$strong1 .= '<strong>';
					$strong2 .= '</strong>';
				}
				else
				{
					unset($strong1);
					unset($strong2);
				}

				$content .= '<tr border="1">';
				if ($skip_read && isset($plan_list->read[$period_id]) && !isset($plan_list->unread[$period_id])) continue;
				$index = $period_id + 1;
				$content .= '<td style="text-align:center">' . $index . '</td><td>' . $strong1 . BfoxLinks::get_ref_link($original) . $strong2 . '</td>';
				if (isset($plan->dates))
				{
					$content .= '<td>';
					if (isset($plan->dates[$period_id])) $content .= $strong1 . date('M d', $plan->dates[$period_id]) . $strong2;
					if (isset($plan_list->unread) || isset($plan_list->read))
					{
						$content .= '</td><td>';
						if (isset($plan_list->unread[$period_id]))
						{
							if (isset($plan_list->read[$period_id]))
								$content .= 'You still need to read ' . BfoxLinks::get_ref_link($plan_list->unread[$period_id]);
							else
								$content .= 'Unread';
							$unread_count++;
							if ($unread_count == $max_unread) break;
						}
						else
						{
							if (isset($plan_list->read[$period_id]))
								$content .= 'Finished';
						}
					}
					$content .= '</td>';
				}
				$content .= '</tr>';
			}
			$content .= '</table></td>';
		}
		$content .= '</tr></table>';
		return $content;
	}

	function bfox_blog_reading_plans($plans, $can_edit = false, $num_cols = 3)
	{
		global $bfox_plan;
		$content = '';
		foreach ($plans as $plan)
		{
			$page = BFOX_MANAGE_PLAN_SUBPAGE;
			$admin_dir = get_option('home') . '/wp-admin';
			$view_url = "$admin_dir/admin.php?page=$page&amp;action=edit&amp;plan_id=$plan->id";

			$content .= "<strong>$plan->name</strong>";
			if ($can_edit) $content .= " (<a href=\"$view_url\">edit</a>)";
			$content .= '<p>';
			if (isset($plan->summary) && ('' != $plan->summary)) $content .= $plan->summary . '<br/>';
			$content .= '</p>';
			$content .= bfox_echo_plan($plan, $num_cols);
			$content .= "<br/>";
		}
		return $content;
	}

	function bfox_get_reading_plan_status()
	{
		global $bfox_plan;
		$plans = $bfox_plan->get_plans();
		$content = '';
		if (0 < count($plans))
		{
			// HACK: hacky way to get a url
			global $bfox_history;
			$url = $bfox_history->get_special_url(false);

			$content .= 'This Bible Study Blog is currently following these reading plans:<br/>';
			foreach ($plans as $plan)
			{
				$content .= "<strong><a href=\"$url\">$plan->name</a></strong>";
				if (isset($plan->summary) && ('' != $plan->summary)) $content .= ': ' .$plan->summary;
				$content .= '<br/>';
			}
		}

		return $content;
	}

	function bfox_plan_summaries($blog_id = 0)
	{
		global $bfox_plan_progress, $bfox_specials;

		if (!$blog_id) $blog_id = $GLOBALS['blog_id'];

		$blog_plan = new PlanBlog($blog_id);
		$blog_plans = $blog_plan->get_plans();
		if (0 < count($blog_plans))
		{
			foreach ($blog_plans as $plan)
			{
				$plan_url = $bfox_specials->get_url_reading_plans($plan->id);
				$content .= "<strong>$plan->name</strong> (<a href=\"$plan_url\">view plan</a>)<br/><i>$plan->summary</i><br/>";
/*				$progress_plan_id = $bfox_plan_progress->get_plan_id($blog_id, $plan->id);
				if (isset($progress_plan_id))
				{
					$refs_object = $bfox_plan_progress->get_plan_refs($progress_plan_id);
					if (isset($refs_object->last_read))
						$content .= 'The furthest you have read is ' . BfoxLinks::get_ref_link($refs_object->read[$refs_object->last_read]) . '.<br/>';
					if (isset($refs_object->first_unread))
						$content .= 'You should read ' . BfoxLinks::get_ref_link($refs_object->unread[$refs_object->first_unread]) . ' next.<br/>';
				}
				else
				{
					$track_url = $bfox_specials->get_url_reading_plans($plan->id, 'track');
					$content .= 'Not tracked. You can choose to <a href="' . $track_url . '">follow this reading plan</a>.<br/>';
				}*/
				if (isset($plan->current_reading))
				{
					$content .= 'The current reading is ' . BfoxLinks::get_ref_link($plan->refs[$plan->current_reading]) . '<br/>';
				}
				else
				{
					if (isset($plan->next_reading)) $content .= 'This plan has not yet started<br/>';
				}
				$content .= '<br/>';
			}
		}
		else
		{
			$content .= 'This Bible Study Blog currently has no reading plans.<br/>';
		}
		return $content;
	}

	function bfox_user_reading_plans($blogs)
	{
		foreach ($blogs as $blog_id => $blog_info)
		{
			$blog_url = $blog_info->siteurl . '/wp-admin/';
			echo "<strong><a href=\"$blog_url\">$blog_info->blogname</a></strong><br/>";
			echo bfox_plan_summaries($blog_id);
			echo "<br/>";
		}
	}

	function bfox_progress_page()
	{
		global $user_ID;
		// Get the bible study blogs for the current user
		$blogs = bfox_get_bible_study_blogs($user_ID);

		echo "<div class=\"wrap\">";
		echo "<h2>Bible Study Blogs</h2>";
		if (0 < count($blogs))
		{
			echo "You are a part of the following Bible Study Blogs:<br/>";
			echo "<ul>";
			foreach ($blogs as $blog_id => $blog_info)
				echo "<li><a href=\"{$blog_info->siteurl}/wp-admin/\">$blog_info->blogname</a></li>";
			echo "</ul>";
		}
		else
			echo "You are not yet a part of any Bible Study Blogs.<br/><br/>";
		$home_dir = get_option('home');
		echo "You can always <a href=\"{$home_dir}/wp-signup.php\">create a new Bible Study Blog</a>. <br/>";
		echo "</div>";

		echo "<div class=\"wrap\">";
		echo "<h2>Reading Plans</h2><br/>";
		if (0 < count($blogs))
		{
			bfox_user_reading_plans($blogs);
		}
		else
		{
			echo "You need to be part of a Bible Study Blog to have a reading plan. Feel free to join one or create your own.<br/>";
		}
		echo "</div>";
	}

	function bfox_can_user_edit_plans()
	{
		// Only level 7 users can edit/create plans
		return current_user_can(BFOX_USER_LEVEL_MANAGE_PLANS);
	}

	function bfox_get_recent_scriptures_output($max = 1, $read = false)
	{
		global $bfox_history;

		$output = '';
		$refs_array = $bfox_history->get_refs_array($max, $read);
		if (0 < count($refs_array))
		{
			$read_str = $read? 'Read' : 'Viewed';
			$lc_read_str = strtolower($read_str);
			$output .= "<h3>Recently $read_str Scriptures<a name=\"recent_{$lc_read_str}\"></a></h3>";
			foreach ($refs_array as &$refs)
			{
				$output .= BfoxLinks::get_ref_link($refs) . '<br/>';
			}
		}
		return $output;
	}

?>