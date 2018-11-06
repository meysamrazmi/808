<?php
/**
 * Themes the role expiration table on the account edit page.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: Associative array of image data, which may include "uri", "alt",
 *     "width", "height", "title" and "attributes".
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * copy image_formatter for lazy loading
 * */
function theme_lazy_image_formatter($variables) {
	$item = $variables['item'];
	$image = array(
		'path' => $item['uri'],
	);

	if (array_key_exists('alt', $item)) {
		$image['alt'] = $item['alt'];
	}
	if (isset($item['attributes'])) {
		$image['attributes'] = $item['attributes'];
	}
	if (isset($item['width']) && isset($item['height'])) {
		$image['width'] = $item['width'];
		$image['height'] = $item['height'];
	}

	// Do not output an empty 'title' attribute.
	if (isset($item['title']) && drupal_strlen($item['title']) > 0) {
		$image['title'] = $item['title'];
	}
	if ($variables['image_style']) {
		$image['style_name'] = $variables['image_style'];

		// Determine the dimensions of the styled image.
		$dimensions = array(
			'width' => $image['width'],
			'height' => $image['height'],
		);
		image_style_transform_dimensions($image['style_name'], $dimensions);
		$image['width'] = $dimensions['width'];
		$image['height'] = $dimensions['height'];

		// Determine the URL for the styled image.
		$variables['path'] = image_style_url($image['style_name'], $image['path']);

		$attributes = isset($item['attributes'])? $image['attributes'] : [];
		$attributes['data-src'] = file_create_url($image['path']);
		foreach (array(
			         'width',
			         'height',
			         'alt',
			         'title',
		         ) as $key) {
			if (isset($image[$key])) {
				$attributes[$key] = $image[$key];
			}
		}
		$output = '<img' . drupal_attributes($attributes) . ' class="lazy" />';
	}
	else {
		$attributes = isset($item['attributes'])? $image['attributes'] : [];
		$attributes['data-src'] = file_create_url($image['path']);
		foreach (array(
			         'width',
			         'height',
			         'alt',
			         'title',
		         ) as $key) {
			if (isset($image[$key])) {
				$attributes[$key] = $image[$key];
			}
		}
		$output = '<img' . drupal_attributes($attributes) . ' class="lazy" />';
	}

	// The link path and link options are both optional, but for the options to be
	// processed, the link path must at least be an empty string.
	if (isset($variables['path']['path'])) {
		$path = $variables['path']['path'];
		$options = isset($variables['path']['options']) ? $variables['path']['options'] : array();

		// When displaying an image inside a link, the html option must be TRUE.
		$options['html'] = TRUE;
		$output = l($output, $path, $options);
	}
	return $output;
}