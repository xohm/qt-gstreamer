#include "memory.h"
#include "buffer.h"

#include <gst/gstminiobject.h>
#include <gst/gstmemory.h>
#include <gst/gstbuffer.h>

namespace QGst {

#ifndef DOXYGEN_RUN
  
// struct QGstMapInfo : GstMapInfo
// {
// };
// 
// struct MapInfo::Data : public QSharedData
// {
//     Data() : QSharedData(), mapinfo(NULL) {}
//     Data(const Data &other);
//     virtual ~Data();
// 
//     QGstMapInfo *mapinfo;
// };
// 
// MapInfo::Data::Data(const MapInfo::Data &other)
//     : QSharedData(other), mapinfo(NULL)
// {
//     if(other.mapinfo) {
// 	memcpy(mapinfo, other.mapinfo, sizeof(QGstMapInfo));
//     }
// }
#endif //DOXYGEN_RUN

MemoryPtr Memory::create(MemoryFlags flags, void *allocator, MemoryPtr parent, size_t maxsize, size_t align, size_t offset, size_t size)
{
    MemoryPtr mem;

    gst_memory_init(mem, static_cast<GstMemoryFlags>(static_cast<int>(flags)), static_cast<GstAllocator *>(allocator), parent, maxsize, align, offset, size);
    return mem;
}

size_t Memory::getSizes(size_t &offset, size_t &maxsize)
{
    return gst_memory_get_sizes(object<GstMemory>(), &offset, &maxsize);
}

bool Memory::map(MapInfo &info, MapFlags flags)
{
    return gst_memory_map(object<GstMemory>(), reinterpret_cast<GstMapInfo *>(&info), static_cast<GstMapFlags>(static_cast<int>(flags)));
}

void Memory::unmap(MapInfo &info)
{
    gst_memory_unmap(object<GstMemory>(), reinterpret_cast<GstMapInfo *>(&info));
}



// MapInfo::MapInfo() : d(new Data)
// {
// }
// 
// MapInfo::~MapInfo()
// {
// }
// 
// MapInfoPtr MapInfo::map_buffer(Buffer *buffer, MapFlags flags)
// {
//     MapInfoPtr info;
//     BufferPtr bptr(buffer);
//     if (!gst_buffer_map(bptr, static_cast<GstMapInfo *>(info), static_cast<GstMapFlags>(static_cast<int>(flags)))) {
//         info.d = NULL;
//     }
//     return info;
// }
// 
// void MapInfo::unmap_buffer(Buffer *buffer)
// {
//     BufferPtr bptr(buffer);
//     gst_buffer_unmap(bptr, d->mapinfo);
// }
// 
// MemoryPtr MapInfo::memory()
// {
//     if (d && d->mapinfo) {
//         //return MemoryPtr(d->mapinfo->memory);
//     }
//     return MemoryPtr();
// }
// 
// MapFlags MapInfo::flags()
// {
//     if (d && d->mapinfo) {
//         return static_cast<MapFlags>(static_cast<int>(d->mapinfo->flags));
//     }
//     return 0;
// }
// 
// const quint8 *MapInfo::data()
// {
//     if (d && d->mapinfo) {
//         return d->mapinfo->data;
//     }
//     return NULL;
// }
// 
// size_t MapInfo::size()
// {
//     if (d && d->mapinfo) {
//         return d->mapinfo->size;
//     }
//     return 0;
// }
// 
// size_t MapInfo::maxsize()
// {
//     if (d && d->mapinfo) {
//         return d->mapinfo->maxsize;
//     }
//     return 0;
// }

} // namespace QGst

