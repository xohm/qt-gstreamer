/*
    Copyright (C) 2013  Diane Trout
      @author Diane Trout <diane@ghic.org>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef QGST_SAMPLE_H
#define QGST_SAMPLE_H

#include "object.h"

namespace QGst {

    /*! \headerfile buffer.h <QGst/Sample>
     * \brief Wrapper class for GstSample
     *
     * Samples are small objects containg data, a type, timing and extra arbitrary information.
     *
     */
class QTGSTREAMER_EXPORT Sample : public Object
{
    QGST_WRAPPER(Sample)
public:
    static SamplePtr create(BufferPtr buffer, CapsPtr caps, void *segment, Structure info);

    BufferPtr buffer();
    CapsPtr caps();
    const Structure info();
    //SegmentPtr segment();
};
} //namespace QGst

QGST_REGISTER_TYPE(QGst::Sample)

#endif
