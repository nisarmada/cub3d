/**
 * Loads an XPM42 texture from the given file path.
 * 
 * @param[in] path The file path to the XPM texture.
 * @returns The XPM texture struct containing its information.
 */
// xpm_t* mlx_load_xpm42(const char* path);

/**
 * Deletes an XPM42 texture by freeing its allocated data.
 * 
 * This will not remove any already drawn XPMs, it simply
 * deletes the XPM buffer.
 * 
 * @param[in] xpm The xpm texture to delete.
 */
// void mlx_delete_xpm42(xpm_t* xpm);

/**
 * Converts a given texture to an image.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] texture The texture to use to create the image from.
 * @return mlx_image_t* The image created from the texture.
 */
// mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);

/**
 * Base object for disk loaded textures.
 * It contains rudementary information about the texture.
 * 
 * @param width The width of the texture.
 * @param height The height of the texture.
 * @param pixels The literal pixel data.
 * @param bytes_per_pixel The amount of bytes in a pixel, always 4.
 */
// typedef struct mlx_texture
// {
// 	uint32_t	width;
// 	uint32_t	height;
// 	uint8_t		bytes_per_pixel;
// 	uint8_t*	pixels;
// }	mlx_texture_t;

/**
 * Struct containing data regarding an XPM image.
 * 
 * @param texture The texture data of the XPM.
 * @param color_count The amount of colors available.
 * @param cpp The amount of characters per pixel.
 * @param mode The color mode, either (c)olor or (m)onochrome.
 */
// typedef struct xpm
// {
// 	mlx_texture_t	texture;
// 	int32_t			color_count;
// 	int32_t			cpp;
// 	char			mode;
// }	xpm_t;