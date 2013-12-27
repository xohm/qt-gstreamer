#include "memory.h"
#include "buffer.h"

#include <gst/gstobject.h>
#include <gst/gstminiobject.h>
#include <gst/gstallocator.h>
#include <gst/gstmemory.h>
#include <gst/gstbuffer.h>

namespace QGst {

MemoryPtr Memory::create(size_t size)
{
    return MemoryPtr::wrap(gst_allocator_alloc(NULL, size, NULL));
}

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

} // namespace QGst

