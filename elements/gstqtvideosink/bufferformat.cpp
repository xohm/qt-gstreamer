/*
    Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies). <qt-info@nokia.com>
    Copyright (C) 2011-2012 Collabora Ltd. <info@collabora.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 2.1
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "bufferformat.h"
#include <QtCore/QByteArray>

BufferFormat BufferFormat::fromCaps(GstCaps *caps)
{
    BufferFormat result;
    if (caps) {
        if (gst_video_info_from_caps(&(result.d->videoInfo), caps)) {
            // FIXME: Raise some kind of error
        }
    }
    return result;
}

/* FIXME: I'm not sure how to fix this.
GstCaps* BufferFormat::newTemplateCaps(GstVideoFormat format)
{
    GstCaps *caps = gst_video_format_new_template_caps(format);

    // workaround for https://bugzilla.gnome.org/show_bug.cgi?id=667681
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    switch (format) {
    case GST_VIDEO_FORMAT_RGB16:
    case GST_VIDEO_FORMAT_BGR16:
    case GST_VIDEO_FORMAT_RGB15:
    case GST_VIDEO_FORMAT_BGR15:
        gst_caps_set_simple(caps, "endianness", G_TYPE_INT, G_LITTLE_ENDIAN, NULL);
        break;
    default:
        break;
    }
#endif
    return caps;
}
*/

GstCaps* BufferFormat::newCaps(GstVideoFormat format, const QSize & size,
                               const Fraction & framerate, const Fraction & pixelAspectRatio)
{
    GstVideoInfo videoInfo;
    gst_video_info_init(&videoInfo);
    gst_video_info_set_format(&videoInfo, format, size.width(), size.height());

    videoInfo.fps_n = framerate.numerator;
    videoInfo.fps_d = framerate.denominator;

    videoInfo.par_n = pixelAspectRatio.numerator;
    videoInfo.par_d = pixelAspectRatio.denominator;

    GstCaps *caps = gst_video_info_to_caps(&videoInfo);

    // workaround for https://bugzilla.gnome.org/show_bug.cgi?id=667681
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    switch (format) {
    case GST_VIDEO_FORMAT_RGB16:
    case GST_VIDEO_FORMAT_BGR16:
    case GST_VIDEO_FORMAT_RGB15:
    case GST_VIDEO_FORMAT_BGR15:
        gst_caps_set_simple(caps, "endianness", G_TYPE_INT, G_LITTLE_ENDIAN, NULL);
        break;
    default:
        break;
    }
#endif

    return caps;
}

inline GstVideoFormat BufferFormat::videoFormat() const
{
    return GST_VIDEO_INFO_FORMAT(&(d->videoInfo));
}

inline GstVideoColorMatrix BufferFormat::colorMatrix() const
{
    return d->videoInfo.colorimetry.matrix;
}

inline QSize BufferFormat::frameSize() const
{
    return QSize(GST_VIDEO_INFO_WIDTH(&(d->videoInfo)),
                 GST_VIDEO_INFO_HEIGHT(&(d->videoInfo)));
}

Fraction BufferFormat::pixelAspectRatio() const
{

    return Fraction(GST_VIDEO_INFO_PAR_N(&(d->videoInfo)),
                    GST_VIDEO_INFO_PAR_D(&(d->videoInfo)));
}

int BufferFormat::bytesPerLine(int component) const
{
    return GST_VIDEO_INFO_PLANE_STRIDE(&(d->videoInfo), component);
}
