<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

  <head>
    <title><?php print $head_title; ?></title>
    <?php print $head; ?>
    <?php print $styles; ?>
    <!--[if lte IE 6]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie6.css";</style><![endif]-->
    <!--[if IE 7]><style type="text/css" media="all">@import "<?php print $base_path . path_to_theme() ?>/css/ie7.css";</style><![endif]-->
    <?php print $scripts; ?>
  </head>

<body class="<?php print $body_classes; ?>">
	<div id="skip-nav"><a href="#content">Skip to Content</a></div>  
	<div id="page">
		<div id="page-inner">
		<!-- ______________________ HEADER _______________________ -->
			<div id="header">
				<div id="header-center">
					<div id="logo-title">
						<div id="name-and-slogan">
							<?php if (!empty($site_name)): ?>
								<h1 id="site-name">
						 			<a href="<?php print $front_page ?>" title="<?php print t('Home'); ?>" rel="home"><?php print $site_name; ?></a>
								</h1>
							<?php endif; ?>
							<?php if (!empty($site_slogan)): ?>
								<div id="site-slogan"><?php print $site_slogan; ?></div>
							<?php endif; ?>
						</div> <!-- /name-and-slogan -->

					</div> <!-- /logo-title -->

					<?php if ($header): ?>
						<div id="header-region">
							<?php print $header; ?>
						</div>
					<?php endif; ?>

					<?php print $search_box; ?>
				</div><!-- /header-center -->
				
				<!-- ______________________ BREADCRUMB (inside the header) ________________ -->

				<div id="bread-line">
					<?php if ($breadcrumb): ?>
						<div id="bread-line-center">
							<?php print $breadcrumb; ?>
						</div><!-- /bread-line-center -->
					<?php endif; ?>
				</div><!-- /bread-line -->
			</div> <!-- /header -->
			
		<!-- ______________________ MAIN NAVIGATION _______________________ -->
		
			<?php if ($main_nav): ?>
				<div id="main-navigation">
					<?php print $main_nav; ?>
				</div> <!-- /main-nav -->
			<?php endif; ?>
			
		<!-- ______________________ MAIN _______________________ -->
		
			<div id="main" class="clearfix">
				<div id="content">
					<div id="content-super">
						<div id="content-inner" class="inner column center">
							<div id="content-sub">
								<?php if ($content_top): ?>
									<div id="content-top">
		 								<?php print $content_top; ?>
									</div> <!-- /#content-top -->
								<?php endif; ?>
								<?php if ($breadcrumb || $title || $mission || $messages || $help || $tabs): ?>
									<div id="content-header">
										<?php if ($title): ?>
											<?php $disallow = array('About Me', 'Contact', 'Portfolio', 'Blog');
											if ($title && !in_array($title, $disallow) && $node->type != portfolio_item): ?>
												<h1 class="title"><?php print $title; ?></h1>
											<?php endif; ?>
										<?php endif; ?>
								
		 						<?php if ($mission): ?>
		   							<div id="mission"><?php print $mission; ?></div>
		 						<?php endif; ?>

		 						<?php if ($show_messages && $messages): print $messages; endif; ?>

		 						<?php print $help; ?> 

		 						<?php if ($tabs): ?>
		   							<div class="tabs"><?php print $tabs; ?></div>
		 						<?php endif; ?>

									</div> <!-- /#content-header -->
							<?php endif; ?>
						
						<!--______________________ CONTENT ______________________-->

						<div id="content-area">
							<?php print $content; ?>
						</div> <!-- /#content-area -->

						<?php print $feed_icons; ?>

						<?php if ($content_bottom): ?>
							<div id="content-bottom">
		 						<?php print $content_bottom; ?>
							</div><!-- /#content-bottom -->
						<?php endif; ?>
					</div><!-- / "content-sub" -->

					<?php if ($right): ?>
						<div id="sidebar-second" class="column sidebar second">
		 					<div id="sidebar-second-inner" class="inner">
		   						<?php print $right; ?>
		 					</div>
						</div>
					<?php endif; ?> <!-- /sidebar-second -->

				</div><!-- / "content-inner" -->
			</div><!-- / "content-super" -->
		</div> <!-- /content-inner /content -->

		<?php if (!empty($primary_links) or !empty($secondary_links)): ?>
			<div id="navigation" class="menu <?php if (!empty($primary_links)) { print "with-main-menu"; } if (!empty($secondary_links)) { print " with-sub-menu"; } ?>">
			<?php if (!empty($primary_links)){ print theme('links', $primary_links, array('id' => 'primary', 'class' => 'links main-menu')); } ?>
			<?php if (!empty($secondary_links)){ print theme('links', $secondary_links, array('id' => 'secondary', 'class' => 'links sub-menu')); } ?>
			</div> <!-- /navigation -->
		<?php endif; ?>

		<?php if ($left): ?>
			<div id="sidebar-first" class="column sidebar first">
				<div id="sidebar-first-inner" class="inner">
				<?php print $left; ?>
				</div><!-- /sidebar-first-inner -->
			</div><!-- /sidebar-first -->
		<?php endif; ?> <!-- /sidebar-left -->
		</div> <!-- /main -->

		<!-- ______________________ FOOTER _______________________ -->

		<?php if(!empty($footer_message) || !empty($footer_block)): ?>
			<div id="footer">
				<div id="footer-inner">
				<?php print $footer_message; ?>
				<?php print $footer_block; ?>
				</div><!-- / "footer-inner" -->
			</div> <!-- /footer -->
		<?php endif; ?>
		</div><!-- / "page-inner" -->
	</div> <!-- /page -->
	<?php print $closure; ?>
</body>
</html>