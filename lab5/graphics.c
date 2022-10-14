#include <lcom/lcf.h>
#include <stdio.h>
#include <string.h>

#define RGB(r,g,b) (r << 16 | g << 8 | b)

#define VBE_FUNC 0x4F
#define SET_VBE_MODE 0x02
#define RET_VBE_MODE_INFO 0x01

static int *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static int *buffer;

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */


void video_refresh()
{
    memcpy(video_mem, buffer, 4 * h_res * v_res);
}

void paint_pixel(uint16_t x, uint16_t y, uint32_t colour) //char* -> byte a byte. pixel a pixel -> mult por bytes/pixel
{
    *(buffer + y * h_res + x) = colour;
}

int file_to_xpm(const char* filepath, xpm_image_t *img)
{
    FILE *file = fopen(filepath, "r");
    char *buff = NULL;
    size_t counter = 0;
    size_t total_size = 0;
    char **xpm = NULL;
    while (!feof(file))
    {
        buff = (char*)malloc(2024);
        fgets(buff, 2024, file);
        buff = (char*)realloc(buff, strlen(buff));
        for (size_t i = 0; i != strlen(buff); i++)
        {
            if (buff[i] == '\n')
            {
                buff[i] = '\0';
                break;
            }
        }
        total_size += strlen(buff);
        xpm = (char**)realloc(xpm, total_size);
        xpm[counter] = buff;
        counter++;
    }
    fclose(file);

    enum xpm_image_type type = XPM_8_8_8_8;
    if (xpm_load((xpm_map_t)(xpm), type, img) == NULL)
        return 1;

    for (int i = 0; i != img->height + 100; i++)
    {
        free(xpm[i]);
    }
    return 0;
}

int paint_xpm(xpm_image_t *img, uint16_t start_x, uint16_t start_y)
{
    if (start_y + img->height > v_res || start_x + img->width > h_res)
        return 1;

    int byte_number = 0;
    for (uint16_t y = 0; y < img->height; y++)
    {
        for (uint16_t x = 0; x < img->width; x++)
        {
            uint32_t colour = RGB(img->bytes[byte_number + 2], img->bytes[byte_number + 1], img->bytes[byte_number]);
            paint_pixel(start_x + x, start_y + y, colour);
            byte_number += 4;
        }
    }
    return 0;
}

void* (vg_init)(uint16_t mode)
{
    vbe_mode_info_t mode_info;
    vbe_get_mode_info(mode, &mode_info);
    h_res = mode_info.XResolution;
    v_res = mode_info.YResolution;
    bits_per_pixel = mode_info.BitsPerPixel;
    int vram_size = (bits_per_pixel + 7) / 8 * h_res * v_res;
    struct minix_mem_range mr;
    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;

    int r;

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) //concede privilégios a SELF para adicionar memória
    {
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
        return NULL;
    }


    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size); //aloca essa memória

    if(video_mem == MAP_FAILED)
    {
        panic("couldn't map video memory");
        return NULL;
    }

    struct reg86 r86;
    memset(&r86, 0, sizeof(r86));	/* zero the structure */
    r86.intno = 0x10;
    r86.ah = VBE_FUNC;
    r86.al = SET_VBE_MODE;
    r86.bx = mode | BIT(14);
    if( sys_int86(&r86) != OK ) {
        panic("\tvg_exit(): sys_int86() failed \n");
        return NULL;
  }
  buffer = malloc(vram_size);
  return video_mem;
}
