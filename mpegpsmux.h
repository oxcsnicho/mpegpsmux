/* 
 * Copyright 2006, 2007, 2008 Fluendo S.A. 
 */

#ifndef __MPEGPSMUX_H__
#define __MPEGPSMUX_H__

#include <gst/gst.h>
#include <gst/base/gstcollectpads.h>
#include <gst/base/gstadapter.h>

G_BEGIN_DECLS

#include "psmux.h"

#define GST_TYPE_MPEG_PSMUX  (mpegpsmux_get_type())
#define GST_MPEG_PSMUX(obj)  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_MPEG_PSMUX, MpegPsMux))

typedef struct MpegPsMux MpegPsMux;
typedef struct MpegPsMuxClass MpegPsMuxClass;
typedef struct MpegPsPadData MpegPsPadData;

typedef GstBuffer * (*MpegPsPadDataPrepareFunction) (GstBuffer * buf,
    MpegPsPadData * data, MpegPsMux * mux);

struct MpegPsMux {
  GstElement parent;

  GstPad *srcpad;

  GstCollectPads *collect; // pads collector

  PsMux *psmux;

  gboolean first;
  GstFlowReturn last_flow_ret;
  
  GstClockTime last_ts;
};

struct MpegPsMuxClass  {
  GstElementClass parent_class;
};

struct MpegPsPadData {
  GstCollectData collect; /* Parent */

  guint8 pid; // XXX: change to stream_id
  guint8 ext_pid; 
  PsMuxStream *stream;

  GstBuffer *queued_buf; /* Currently pulled buffer */
  GstClockTime cur_ts; /* Adjusted TS for the pulled buffer */
  GstClockTime last_ts; /* Most recent valid TS for this stream */

  GstBuffer * codec_data; /* Optional codec data available in the caps */

  MpegPsPadDataPrepareFunction prepare_func; /* Handler to prepare input data */

  gboolean eos;
};

GType mpegpsmux_get_type (void);

#define CLOCK_BASE 9LL
#define CLOCK_FREQ (CLOCK_BASE * 10000)

#define MPEGTIME_TO_GSTTIME(time) (gst_util_uint64_scale ((time), \
                        GST_MSECOND/10, CLOCK_BASE))
#define GSTTIME_TO_MPEGTIME(time) (gst_util_uint64_scale ((time), \
                        CLOCK_BASE, GST_MSECOND/10))

#define NORMAL_TS_PACKET_LENGTH 188
#define M2TS_PACKET_LENGTH      192
#define STANDARD_TIME_CLOCK     27000000
/*33 bits as 1 ie 0x1ffffffff*/
#define TWO_POW_33_MINUS1     ((0xffffffff * 2) - 1) 
G_END_DECLS

#endif
