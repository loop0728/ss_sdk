/*
 * u_uvc.h
 *
 * Utility definitions for the uvc function
 *
 * Copyright (c) 2013-2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzej.p@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef U_UVC_H
#define U_UVC_H

#include <linux/usb/composite.h>
#include <linux/usb/video.h>

#ifndef CONFIG_MULTI_STREAM_FUNC_NUM
#define CONFIG_MULTI_STREAM_FUNC_NUM 1
#endif

#define MAX_STREAM_SUPPORT 4
#define DEFAULT_STREAM_NAME "UVC Camera"
#define MULTI_STREAM_NUM CONFIG_MULTI_STREAM_FUNC_NUM

#if (MULTI_STREAM_NUM>1)
#define CONFIG_SS_GADGET_UVC_MULTI_STREAM
#endif

#define fi_to_f_uvc_opts(f)	container_of(f, struct f_uvc_opts, func_inst)
#define fuvc_to_gadget(f)   (f.config->cdev->gadget)
#ifdef CONFIG_SS_GADGET_UVC_MULTI_STREAM
#define video_to_stream(f)     container_of(f, struct uvc_streaming, video)
#define video_to_uvc(f)      (video_to_stream(f))->dev
#else
#define video_to_uvc(f)     container_of(f, struct uvc_device, video)
#endif

struct f_uvc_opts {
	struct usb_function_instance			func_inst;
	unsigned int					uvc_gadget_trace_param;
#ifdef CONFIG_SS_GADGET_UVC_MULTI_STREAM
	unsigned int					streaming_interval[MAX_STREAM_SUPPORT];
	unsigned int					streaming_maxpacket[MAX_STREAM_SUPPORT];
	unsigned int					streaming_maxburst[MAX_STREAM_SUPPORT];
	const char *					streaming_name[MAX_STREAM_SUPPORT];
#else
	unsigned int					streaming_interval;
	unsigned int					streaming_maxpacket;
	unsigned int					streaming_maxburst;
	const char *					streaming_name;
#endif

#if defined(CONFIG_SS_GADGET) || defined(CONFIG_SS_GADGET_MODULE)
	bool						bulk_streaming_ep;
#endif
	/*
	 * Control descriptors array pointers for full-/high-speed and
	 * super-speed. They point by default to the uvc_fs_control_cls and
	 * uvc_ss_control_cls arrays respectively. Legacy gadgets must
	 * override them in their gadget bind callback.
	 */
	const struct uvc_descriptor_header * const	*fs_control;
	const struct uvc_descriptor_header * const	*ss_control;

	/*
	 * Streaming descriptors array pointers for full-speed, high-speed and
	 * super-speed. They will point to the uvc_[fhs]s_streaming_cls arrays
	 * for configfs-based gadgets. Legacy gadgets must initialize them in
	 * their gadget bind callback.
	 */
	const struct uvc_descriptor_header * const	*fs_streaming;
	const struct uvc_descriptor_header * const	*hs_streaming;
	const struct uvc_descriptor_header * const	*ss_streaming;

	/* Default control descriptors for configfs-based gadgets. */
	struct uvc_camera_terminal_descriptor		uvc_camera_terminal;
	struct uvc_processing_unit_descriptor		uvc_processing;
	struct uvc_output_terminal_descriptor		uvc_output_terminal;
	struct uvc_color_matching_descriptor		uvc_color_matching;

	/*
	 * Control descriptors pointers arrays for full-/high-speed and
	 * super-speed. The first element is a configurable control header
	 * descriptor, the other elements point to the fixed default control
	 * descriptors. Used by configfs only, must not be touched by legacy
	 * gadgets.
	 */
	struct uvc_descriptor_header			*uvc_fs_control_cls[5];
	struct uvc_descriptor_header			*uvc_ss_control_cls[5];

	/*
	 * Streaming descriptors for full-speed, high-speed and super-speed.
	 * Used by configfs only, must not be touched by legacy gadgets. The
	 * arrays are allocated at runtime as the number of descriptors isn't
	 * known in advance.
	 */
	struct uvc_descriptor_header			**uvc_fs_streaming_cls;
	struct uvc_descriptor_header			**uvc_hs_streaming_cls;
	struct uvc_descriptor_header			**uvc_ss_streaming_cls;

	/*
	 * Read/write access to configfs attributes is handled by configfs.
	 *
	 * This lock protects the descriptors from concurrent access by
	 * read/write and symlink creation/removal.
	 */
	struct mutex			lock;
	int				refcnt;
};

void uvc_set_trace_param(unsigned int trace);

#endif /* U_UVC_H */

