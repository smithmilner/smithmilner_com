<div class="node portfolio-item <?php print $classes; ?>" id="node-<?php print $node->nid; ?>">
  <div class="node-inner">
	
	<div id="item-header">
    	<?php if ($title): ?>
	      <h2 class="title"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
	    <?php endif; ?>

		<?php if ($field_port_categories): ?>
				<h4 class="port-categories">Category: <a href="/portfolio-category/<?php print $field_port_categories[0]['view']; ?>" title="<?php print $field_port_categories[0]['view']; ?> Items" ><?php print $field_port_categories[0]['view']; ?></h4></a>
		<?php endif; ?>

		<?php if ($field_port_webaddress): ?>
			<div class="field field-type-link field-field-port-webaddress">
				<strong><span class="port-address-label">Address:</span> <?php print $field_port_webaddress[0]['view'];?></strong>
			</div>
		<?php endif; ?>
		
   		<?php if ($submitted): ?>
	      <span class="submitted"><strong><?php print $submitted; ?></strong></span>
	    <?php endif; ?>

		
	</div><!-- / "item-header" -->

	<?php if ($content): ?>
    <div class="content">
      <?php print $node->content['body']['#value']; ?>
    </div>
	<?php endif; ?>
	
	<script type="text/javascript">
	$(function() {
		$('a.lightbox').lightBox(); // Select all links with lightbox class
	});
	</script>
	
	<?php if ($page): ?>
		<?php $i = 0; ?>
		<?php if ($field_port_images[0]['filename']): ?>
			<div id="port-images">
				<h3 class="port-image-header">Portfolio Item Images</h3>
				<div id="slider">    
			        <div class="scrollButtons left">left</div>
					<div style="overflow: hidden;" class="scroll">
						<div class="scrollContainer">
			                <?php while ($field_port_images[$i]) { ?>
								<?php $s = $i + 1; ?>
								<div class="panel" id="panel_<?php print $s; ?>">
									<div class="inside">
										<a href="/<?php print $node->field_port_images[$i]['filepath']; ?>" class="lightbox"><?php print theme('imagecache', 'port-item_326b240/portfolio-images', $node->field_port_images[$i]['filename']); ?></a>
										<h3><?php print $field_port_images[$i]['data']['title']; ?></h3>
										<p><?php print $field_port_images[$i]['data']['description']; ?></p>
										<?php $i++; ?>
									</div><!-- /inside -->
								</div><!-- /panel -->
								<?php } ?>
			            </div>
						<div id="left-shadow"></div>
						<div id="right-shadow"></div>
			        </div>
					<div class="scrollButtons right">right</div>
			    </div>
			</div><!-- / "port-images" -->
		<?php endif; ?>
	<?php endif; ?>
	
	<div class="portfolio-footer">
		<?php if ($links): ?> 
	      <div class="links"><?php print $links; ?></div>
		<?php endif; ?>

		<?php if ($terms): ?>
	      <div class="taxonomy"><?php print $terms; ?></div>
	    <?php endif;?>
	</div><!-- / "portfolio-footer" -->
	
  </div> <!-- /node-inner -->
</div> <!-- /node-->