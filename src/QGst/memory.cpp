#include "memory.h"

#include <gst/gstminiobject.h>
#include <gst/gstmemory.h>

namespace QGst {

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

// bool Memory::map(MapInfo &info, MapFlags flags)
// {
// //    return gst_memory_map(object<GstMemory>(), &(info.d.mapinfo), flags);
// }

// void Memory::unmap(MapInfo &info)
// {
// //    gst_memory_unmap(object<GstMemory>(), &(info.d.mapinfo));
// }

#ifndef DOXYGEN_RUN
// struct MapInfo::Data : public QSharedData
// {
//     Data() : QSharedData(), mapinfo(NULL) {}
//     Data(const Data &other);
//     virtual ~Data();

//     GstMapInfo *mapinfo;
// };

// MapInfo::Data::Data(const MapInfo::Data &other)
//     : QSharedData(other), mapinfo(NULL)
// {
//     if(other.mapinfo) {
// 	memcpy(mapinfo, other.mapinfo, sizeof(GstMapInfo));
//     }
// }
#endif //DOXYGEN_RUN
} // namespace QGst

