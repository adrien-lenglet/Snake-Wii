/*
** EPITECH PROJECT, 2018
** __xd__world
** File description:
** various loaders : valid within a gl context
*/

#include "headers.h"

#define DEFAULT_FIFO_SIZE (256 * 1024)

void init(void)
{
    thread_init();
    srand(time(NULL));
    load_gl_fun();
    _demo->buf.cull_state = 1;
	f32 yscale;
	u32 xfbHeight;
	_demo->buf.fb = 0;
	GXTexObj texture;
	void *gpfifo = NULL;
    GXRModeObj *rmode = NULL;
	GXColor background = {0x00, 0x00, 0x00, 0xFF};
	TPLFile cubeTPL;

	VIDEO_Init();
	WPAD_Init();
    PAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);

	// allocate the fifo buffer
	gpfifo = memalign(32, DEFAULT_FIFO_SIZE);
	memset(gpfifo, 0, DEFAULT_FIFO_SIZE);

	// allocate 2 framebuffers for double buffering
	_demo->buf.frameBuffer[0] = SYS_AllocateFramebuffer(rmode);
	_demo->buf.frameBuffer[1] = SYS_AllocateFramebuffer(rmode);

	// configure video
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(_demo->buf.frameBuffer[_demo->buf.fb]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

	_demo->buf.fb ^= 1;

	// init the flipper
	GX_Init(gpfifo, DEFAULT_FIFO_SIZE);

	// clears the bg to color and clears the z buffer
	GX_SetCopyClear(background, 0x00FFFFFF);

	// other gx setup
	GX_SetViewport(0,0,rmode->fbWidth,rmode->efbHeight,0,1);
	yscale = GX_GetYScaleFactor(rmode->efbHeight,rmode->xfbHeight);
	xfbHeight = GX_SetDispCopyYScale(yscale);
	GX_SetScissor(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopySrc(0,0,rmode->fbWidth,rmode->efbHeight);
	GX_SetDispCopyDst(rmode->fbWidth,xfbHeight);
	GX_SetCopyFilter(rmode->aa,rmode->sample_pattern,GX_TRUE,rmode->vfilter);
	GX_SetFieldMode(rmode->field_rendering,((rmode->viHeight==2*rmode->xfbHeight)?GX_ENABLE:GX_DISABLE));

	if (rmode->aa) {
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	} else {
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
	}

	GX_SetCullMode(GX_CULL_NONE);
	GX_CopyDisp(_demo->buf.frameBuffer[_demo->buf.fb],GX_TRUE);
	GX_SetDispCopyGamma(GX_GM_1_0);

	// setup the vertex attribute table
	// describes the data
	// args: vat location 0-7, type of data, data format, size, scale
	// so for ex. in the first call we are sending position data with
	// 3 values X,Y,Z of size F32. scale sets the number of fractional
	// bits for non float data.
	GX_ClearVtxDesc();
	GX_SetVtxDesc(GX_VA_POS, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_NRM, GX_DIRECT);
	GX_SetVtxDesc(GX_VA_TEX0, GX_DIRECT);

	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);

	// set number of rasterized color channels
	GX_SetNumChans(1);

	//set number of textures to generate
	GX_SetNumTexGens(1);

	GX_InvVtxCache();
	GX_InvalidateTexAll();

	TPL_OpenTPLFromMemory(&cubeTPL, (void *)textures_tpl, textures_tpl_size);
	TPL_GetTexture(&cubeTPL, yoshi, &texture);
	// setup our camera at the origin
	// looking down the -z axis with y up
	// setup our projection matrix
	// this creates a perspective matrix with a view angle of 90,
	// and aspect ratio based on the display resolution
	_demo->win.w = rmode->viWidth;
	_demo->win.h = rmode->viHeight;

    CON_Init(_demo->buf.frameBuffer[0], 0, 0, rmode->fbWidth, rmode->efbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    VIDEO_SetBlack(FALSE);
    //world_render();
    GX_SetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GX_SetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GX_SetAlphaUpdate(GX_TRUE);
    GX_SetColorUpdate(GX_TRUE);
}

void quit(void)
{
    thread_quit();
}

static void gl_gen_ext(void)
{
    /*glGenRenderbuffers(1, &_demo->buf.hdr_depthbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _demo->buf.hdr_depthbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
    _demo->win.w, _demo->win.h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_RENDERBUFFER, _demo->buf.hdr_depthbuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
    _demo->buf.hdr_render_texture, 0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1,
    _demo->buf.dist_texture, 0);
    glDrawBuffers(2, (glenum[]){GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1});
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _demo->buf.msgs = vec_msg_entry_create();*/
}

void gl_gen(demo_t *demo)
{
    demo->buf.to_draw = vec_render_call_init();
    /*glGenFramebuffers(1, &_demo->buf.hdr_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _demo->buf.hdr_framebuffer);
    glGenTextures(1, &_demo->buf.hdr_render_texture);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.hdr_render_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _demo->win.w, _demo->win.h, 0,
    GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenTextures(1, &_demo->buf.dist_texture);
    glBindTexture(GL_TEXTURE_2D, _demo->buf.dist_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, _demo->win.w, _demo->win.h, 0,
    GL_RGBA, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/
    gl_gen_ext();
}

void gl_delete(demo_t *demo)
{
    vec_render_call_destroy(demo->buf.to_draw);
    vec_msg_entry_destroy(&_demo->buf.msgs);
}
