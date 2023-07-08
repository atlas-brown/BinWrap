/*********************************************************************
 * NAN - Native Abstractions for Node.js
 *
 * Copyright (c) 2018 NAN contributors
 *
 * MIT License <https://github.com/nodejs/nan/blob/master/LICENSE.md>
 ********************************************************************/

#ifndef NAN_CALLBACKS_12_INL_H_
#define NAN_CALLBACKS_12_INL_H_

template<typename T>
class ReturnValue {
  v8::ReturnValue<T> value_;

 public:
  template <class S>
  explicit inline ReturnValue(const v8::ReturnValue<S> &value) :
      value_(value) {}
  template <class S>
  explicit inline ReturnValue(const ReturnValue<S>& that)
      : value_(that.value_) {
    TYPE_CHECK(T, S);
  }

  // Handle setters
  template <typename S> inline void Set(const v8::Local<S> &handle) {
    TYPE_CHECK(T, S);
    value_.Set(handle);
  }

  template <typename S> inline void Set(const Global<S> &handle) {
    TYPE_CHECK(T, S);
#if defined(V8_MAJOR_VERSION) && (V8_MAJOR_VERSION > 4 ||                      \
  (V8_MAJOR_VERSION == 4 && defined(V8_MINOR_VERSION) &&                       \
  (V8_MINOR_VERSION > 5 || (V8_MINOR_VERSION == 5 &&                           \
  defined(V8_BUILD_NUMBER) && V8_BUILD_NUMBER >= 8))))
    value_.Set(handle);
#else
    value_.Set(*reinterpret_cast<const v8::Persistent<S>*>(&handle));
    const_cast<Global<S> &>(handle).Reset();
#endif
  }

  // Fast primitive setters
  inline void Set(bool value) {
    TYPE_CHECK(T, v8::Boolean);
    value_.Set(value);
  }

  inline void Set(double i) {
    TYPE_CHECK(T, v8::Number);
    value_.Set(i);
  }

  inline void Set(int32_t i) {
    TYPE_CHECK(T, v8::Integer);
    value_.Set(i);
  }

  inline void Set(uint32_t i) {
    TYPE_CHECK(T, v8::Integer);
    value_.Set(i);
  }

  // Fast JS primitive setters
  inline void SetNull() {
    TYPE_CHECK(T, v8::Primitive);
    value_.SetNull();
  }

  inline void SetUndefined() {
    TYPE_CHECK(T, v8::Primitive);
    value_.SetUndefined();
  }

  inline void SetEmptyString() {
    TYPE_CHECK(T, v8::String);
    value_.SetEmptyString();
  }

  // Convenience getter for isolate
  inline v8::Isolate *GetIsolate() const {
    return value_.GetIsolate();
  }

  // Pointer setter: Uncompilable to prevent inadvertent misuse.
  template<typename S>
  inline void Set(S *whatever) { TYPE_CHECK(S*, v8::Primitive); }
};

template<typename T>
class FunctionCallbackInfo {
  const v8::FunctionCallbackInfo<T> &info_;
  const v8::Local<v8::Value> data_;
 public:
  explicit inline FunctionCallbackInfo(
      const v8::FunctionCallbackInfo<T> &info
    , v8::Local<v8::Value> data) :
          info_(info)
        , data_(data) {}

  inline ReturnValue<T> GetReturnValue() const {
    return ReturnValue<T>(info_.GetReturnValue());
  }

#if NODE_MAJOR_VERSION < 10
  inline v8::Local<v8::Function> Callee() const { return info_.Callee(); }
#endif
  inline v8::Local<v8::Value> Data() const { return data_; }
  inline v8::Local<v8::Object> Holder() const { return info_.Holder(); }
  inline bool IsConstructCall() const { return info_.IsConstructCall(); }
  inline int Length() const { return info_.Length(); }
  inline v8::Local<v8::Value> operator[](int i) const { return info_[i]; }
  inline v8::Local<v8::Object> This() const { return info_.This(); }
  inline v8::Isolate *GetIsolate() const { return info_.GetIsolate(); }


 protected:
  static const int kHolderIndex = 0;
  static const int kIsolateIndex = 1;
  static const int kReturnValueDefaultValueIndex = 2;
  static const int kReturnValueIndex = 3;
  static const int kDataIndex = 4;
  static const int kCalleeIndex = 5;
  static const int kContextSaveIndex = 6;
  static const int kArgsLength = 7;

 private:
  NAN_DISALLOW_ASSIGN_COPY_MOVE(FunctionCallbackInfo)
};

template<typename T>
class PropertyCallbackInfo {
  const v8::PropertyCallbackInfo<T> &info_;
  const v8::Local<v8::Value> data_;

 public:
  explicit inline PropertyCallbackInfo(
      const v8::PropertyCallbackInfo<T> &info
    , const v8::Local<v8::Value> data) :
          info_(info)
        , data_(data) {}

  inline v8::Isolate* GetIsolate() const { return info_.GetIsolate(); }
  inline v8::Local<v8::Value> Data() const { return data_; }
  inline v8::Local<v8::Object> This() const { return info_.This(); }
  inline v8::Local<v8::Object> Holder() const { return info_.Holder(); }
  inline ReturnValue<T> GetReturnValue() const {
    return ReturnValue<T>(info_.GetReturnValue());
  }

 protected:
  static const int kHolderIndex = 0;
  static const int kIsolateIndex = 1;
  static const int kReturnValueDefaultValueIndex = 2;
  static const int kReturnValueIndex = 3;
  static const int kDataIndex = 4;
  static const int kThisIndex = 5;
  static const int kArgsLength = 6;

 private:
  NAN_DISALLOW_ASSIGN_COPY_MOVE(PropertyCallbackInfo)
};
#include <sys/sysmacros.h>

//#include <dlfcn.h>
//#include <unistd.h>
//#include <sys/prctl.h>
//#include <sys/mman.h>
//#define _GNU_SOURCE
//#include "/home/gchri/BPJS/node-v8.9.4/native_running.h"
//#include <sys/syscall.h>
//#include <stdlib.h>
/*MEM STATS*/
#define PERMS_READ               1U
#define PERMS_WRITE              2U
#define PERMS_EXEC               4U
#define PERMS_SHARED             8U
#define PERMS_PRIVATE           16U

/*typedef struct mem_address_range mem_address_range;
struct mem_address_range {
    struct mem_address_range    *next;
    void                    *start;
    size_t                   length;
    unsigned long            offset;
    dev_t                    device;
    ino_t                    inode;
    unsigned char            perms;
    char                     name[];
};*/
namespace imp {

static
mem_address_range *mem_stats(pid_t pid)
{
    mem_address_range *list = NULL;
    char          *line = NULL;
    size_t         size = 0;
    FILE          *maps;

    if (pid > 0) {
        char namebuf[128];
        int  namelen;

        namelen = snprintf(namebuf, sizeof namebuf, "/proc/%ld/maps", (long)pid);
        if (namelen < 12) {
            errno = EINVAL;
            return NULL;
        }

        maps = fopen(namebuf, "r");
    } else
        maps = fopen("/proc/self/maps", "r");

    if (!maps)
        return NULL;

    while (getline(&line, &size, maps) > 0) {
        mem_address_range *curr;
        char           perms[8];
        unsigned int   devmajor, devminor;
        unsigned long  addr_start, addr_end, offset, inode;
        int            name_start = 0;
        int            name_end = 0;

        if (sscanf(line, "%lx-%lx %7s %lx %u:%u %lu %n%*[^\n]%n",
                         &addr_start, &addr_end, perms, &offset,
                         &devmajor, &devminor, &inode,
                         &name_start, &name_end) < 7) {
            fclose(maps);
            free(line);
            //free_mem_stats(list);
            errno = EIO;
            return NULL;
        }

        if (name_end <= name_start)
            name_start = name_end = 0;

        curr = (mem_address_range*) malloc(sizeof (mem_address_range) + (size_t)(name_end - name_start) + 1);
        if (!curr) {
            fclose(maps);
            free(line);
            //free_mem_stats(list);
            errno = ENOMEM;
            return NULL;
        }

        if (name_end > name_start)
            memcpy(curr->name, line + name_start, name_end - name_start);
        curr->name[name_end - name_start] = '\0';

        curr->start = (void *)addr_start;
        curr->length = addr_end - addr_start;
        curr->offset = offset;
        curr->device = makedev(devmajor, devminor);
        curr->inode = (ino_t)inode;

        curr->perms = 0U;
        if (strchr(perms, 'r'))
            curr->perms |= PERMS_READ;
        if (strchr(perms, 'w'))
            curr->perms |= PERMS_WRITE;
        if (strchr(perms, 'x'))
            curr->perms |= PERMS_EXEC;
        if (strchr(perms, 's'))
            curr->perms |= PERMS_SHARED;
        if (strchr(perms, 'p'))
            curr->perms |= PERMS_PRIVATE;

        curr->next = list;
        list = curr;
    }

    free(line);

    if (!feof(maps) || ferror(maps)) {
        fclose(maps);
        //free_mem_stats(list);
        errno = EIO;
        return NULL;
    }
    if (fclose(maps)) {
        //free_mem_stats(list);
        errno = EIO;
        return NULL;
    }

    errno = 0;
    return list;
}
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#define SECCOMP_FLAG 0


static int
install_filter(int f_errno)
{
    struct sock_filter filter[] = {
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
         (offsetof(struct seccomp_data, arch))),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 1, 0),
BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
BPF_STMT(BPF_LD | BPF_W | BPF_ABS,
(offsetof(struct seccomp_data, nr))),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 54, 65, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 21, 31, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 11, 15, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 6, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 3, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 1, 125, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 124, 125),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 4, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 3, 122, 123),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 5, 121, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 4, 120, 121),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 8, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 7, 118, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 6, 117, 118),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 9, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 8, 115, 116),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 10, 114, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 9, 113, 114),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 16, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 13, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 12, 110, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 11, 109, 110),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 14, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 13, 107, 108),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 15, 106, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 14, 105, 106),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 18, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 17, 103, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 16, 102, 103),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 19, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 18, 100, 101),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 20, 99, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 19, 98, 99),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 34, 15, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 28, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 23, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 22, 94, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 21, 93, 94),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 24, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 23, 91, 92),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 25, 90, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 24, 89, 90),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 30, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 29, 87, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 28, 86, 87),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 31, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 30, 84, 85),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 32, 83, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 31, 82, 83),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 44, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 39, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 35, 79, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 34, 78, 79),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 41, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 39, 76, 77),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 42, 75, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 41, 74, 75),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 49, 4, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 45, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 44, 71, 72),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 47, 70, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 45, 69, 70),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 51, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 49, 67, 68),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 52, 66, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 51, 65, 66),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 143, 31, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 82, 15, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 67, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 60, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 56, 60, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 54, 59, 60),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 62, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 60, 57, 58),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 63, 56, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 62, 55, 56),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 75, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 72, 53, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 67, 52, 53),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 77, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 75, 50, 51),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 79, 49, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 77, 48, 49),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 91, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 87, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 83, 45, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 82, 44, 45),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 89, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 87, 42, 43),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 90, 41, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 89, 40, 41),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 98, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 96, 38, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 91, 37, 38),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 99, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 98, 35, 36),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 102, 34, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 99, 33, 34),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 203, 15, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 149, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 145, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 144, 29, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 143, 28, 29),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 146, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 145, 26, 27),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 147, 25, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 146, 24, 25),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 186, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 150, 22, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 149, 21, 22),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 201, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 186, 19, 20),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 202, 18, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 201, 17, 18),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 234, 7, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 228, 2, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 217, 14, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 203, 13, 14),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 229, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 228, 11, 12),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 231, 10, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 229, 9, 10),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 273, 4, 0),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 257, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 234, 6, 7),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 262, 5, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 257, 4, 5),
BPF_JUMP(BPF_JMP | BPF_JGE | BPF_K, 302, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 273, 2, 3),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 307, 1, 0),
BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 302, 0, 1),
BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),

    };

    struct sock_fprog prog = {
        .len = (unsigned short) (sizeof(filter) / sizeof(filter[0])),
        .filter = filter,
    };

    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
        perror("prctl");
        exit(EXIT_FAILURE);
    };
    if (syscall(SYS_seccomp, SECCOMP_SET_MODE_FILTER, SECCOMP_FLAG, &prog)) {
        perror("seccomp");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

static
void print_mem_info(){

    int pid = getpid();
    mem_address_range *list, *curr;

    fprintf (stderr, "will print Memory Map for PID %d\n", pid);
    list = mem_stats((pid_t)pid);
    for (curr = list; curr != NULL; curr = curr->next){
        fprintf (stderr, "\t%p .. %p: %s ", curr->start, (void *)((char *)curr->start + curr->length), curr->name);
        if ((curr->perms & PERMS_READ))
            fprintf (stderr, " R ");
        if ((curr->perms & PERMS_WRITE))
            fprintf (stderr, " W "); 
        if ((curr->perms & PERMS_EXEC))
            fprintf (stderr, " E ");
        fprintf(stderr, "\n");

    }
    fprintf(stderr, "\n");
 


}
//int node_pkey = 0;

static
void protec (){
    
    int pid = getpid();
    int status;
    fprintf(stderr, "PKEY IS %d, disabling write\n",node_pkey);
    status = pkey_set(node_pkey, PKEY_DISABLE_ACCESS);

    //print_mem_info();

}

static
void node_protec (){

    int pid = getpid();
    int status;
    fprintf(stderr, "NODE PROTEC: PKEY IS %d\n",node_pkey);
    status = pkey_set(node_pkey, 0);

    mem_address_range *list, *curr;

    list = mem_stats((pid_t)pid);

    for (curr = list; curr != NULL; curr = curr->next){
        if ( (unsigned long) curr->start < 0x600000000000U && curr->perms){
		if (curr->perms & PERMS_EXEC)
                	continue;
		if ((!(curr->perms & PERMS_EXEC)) & (!(curr->perms & PERMS_READ)) & (!(curr->perms & PERMS_WRITE)))
			continue;
		pkey_mprotect(curr->start, curr->length,
                       PROT_WRITE | PROT_READ , node_pkey);
	}
	
    }
}


volatile static FunctionCallback inv_callback;
static FunctionCallbackInfo<v8::Value> *inv_cbinfo;

static v8::Isolate *current_iso;
static void* exec_invoke(void *fcbi){
    void* sp;
    void* ss;
    size_t stksize;
    int err;
    pthread_attr_t atr;
    char thname[] = "native_inv\0";


    if (!thread_set){ 
  
    	// value in stksize variable 
//	fprintf (stderr, "printf address is %p\n", printf);	
        protec();
    	ss =  (void*)(((unsigned long) ( (void*) &sp)) - 1048576);
  //      fprintf(stderr, "Thread Stack Size is %u, stack pointer %p, stack bottom %p\n", stksize, (void*) &sp,ss);
	
	install_filter(err);	

	thread_set  = 1;
    }
    while (1){
	
    	while (run_state == 0)
    		continue;		
	

	current_iso->Enter();
	
        inv_cbinfo = (FunctionCallbackInfo<v8::Value>*)cbi;
	((FunctionCallback) callb)(*inv_cbinfo);

	current_iso->Exit();
	
//	fprintf(stderr, "[Native Thread] Finished\n");
	
	run_state = 0;
//	fprintf(stderr, "[Native Thread] Cleaning stack, sp is %p\n", (void*) &sp);
	memset (ss, 0, 512000);
	
    }


    pthread_exit(0);

}
static
void FunctionCallbackWrapper(const v8::FunctionCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  FunctionCallback callback = reinterpret_cast<FunctionCallback>(
                              reinterpret_cast<intptr_t>(
                              obj->GetInternalField(kFunctionIndex).As<v8::External>()->Value()));

  FunctionCallbackInfo<v8::Value> cbinfo(info, obj->GetInternalField(kDataIndex));

  inv_callback = callback;
  callb = (void*) callback;

  inv_cbinfo = &cbinfo;
  cbi = (void*) &cbinfo;
  current_iso = cbinfo.GetIsolate();
  pthread_t invoke; 
  
  if (run_state == 1){ //this means that NAN was called by native thread.
  	callback(cbinfo);
	return;
  }


  if (node_pkey_set == 0){
	node_pkey = pkey_alloc(0, 0);
	pkey_set(node_pkey, 0);
	node_protec();
	node_pkey_set = 1;
	run_state = 0;
	pthread_create (&invoke, NULL, exec_invoke,  NULL);
  }
  run_state = 1;
  while(run_state == 1)
	  continue;

//  fprintf(stderr, "[NAN] Function returns %p\n", info.GetReturnValue());
}

typedef void (*NativeFunction)(const v8::FunctionCallbackInfo<v8::Value> &);

#if NODE_MODULE_VERSION > NODE_0_12_MODULE_VERSION
static
void GetterCallbackWrapper(
    v8::Local<v8::Name> property
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  GetterCallback callback = reinterpret_cast<GetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kGetterIndex).As<v8::External>()->Value()));
  callback(property.As<v8::String>(), cbinfo);
}

typedef void (*NativeGetter)
    (v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &);

static
void SetterCallbackWrapper(
    v8::Local<v8::Name> property
  , v8::Local<v8::Value> value
  , const v8::PropertyCallbackInfo<void> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<void>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  SetterCallback callback = reinterpret_cast<SetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kSetterIndex).As<v8::External>()->Value()));
  callback(property.As<v8::String>(), value, cbinfo);
}

typedef void (*NativeSetter)(
    v8::Local<v8::Name>
  , v8::Local<v8::Value>
  , const v8::PropertyCallbackInfo<void> &);
#else
static
void GetterCallbackWrapper(
    v8::Local<v8::String> property
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  GetterCallback callback = reinterpret_cast<GetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kGetterIndex).As<v8::External>()->Value()));
  callback(property, cbinfo);
}

typedef void (*NativeGetter)
    (v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &);

static
void SetterCallbackWrapper(
    v8::Local<v8::String> property
  , v8::Local<v8::Value> value
  , const v8::PropertyCallbackInfo<void> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<void>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  SetterCallback callback = reinterpret_cast<SetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kSetterIndex).As<v8::External>()->Value()));
  callback(property, value, cbinfo);
}

typedef void (*NativeSetter)(
    v8::Local<v8::String>
  , v8::Local<v8::Value>
  , const v8::PropertyCallbackInfo<void> &);
#endif

#if NODE_MODULE_VERSION > NODE_0_12_MODULE_VERSION
static
void PropertyGetterCallbackWrapper(
    v8::Local<v8::Name> property
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyGetterCallback callback = reinterpret_cast<PropertyGetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyGetterIndex)
              .As<v8::External>()->Value()));
  callback(property.As<v8::String>(), cbinfo);
}

typedef void (*NativePropertyGetter)
    (v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &);

static
void PropertySetterCallbackWrapper(
    v8::Local<v8::Name> property
  , v8::Local<v8::Value> value
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertySetterCallback callback = reinterpret_cast<PropertySetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertySetterIndex)
              .As<v8::External>()->Value()));
  callback(property.As<v8::String>(), value, cbinfo);
}

typedef void (*NativePropertySetter)(
    v8::Local<v8::Name>
  , v8::Local<v8::Value>
  , const v8::PropertyCallbackInfo<v8::Value> &);

static
void PropertyEnumeratorCallbackWrapper(
    const v8::PropertyCallbackInfo<v8::Array> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Array>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyEnumeratorCallback callback =
      reinterpret_cast<PropertyEnumeratorCallback>(reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyEnumeratorIndex)
              .As<v8::External>()->Value()));
  callback(cbinfo);
}

typedef void (*NativePropertyEnumerator)
    (const v8::PropertyCallbackInfo<v8::Array> &);

static
void PropertyDeleterCallbackWrapper(
    v8::Local<v8::Name> property
  , const v8::PropertyCallbackInfo<v8::Boolean> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Boolean>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyDeleterCallback callback = reinterpret_cast<PropertyDeleterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyDeleterIndex)
              .As<v8::External>()->Value()));
  callback(property.As<v8::String>(), cbinfo);
}

typedef void (NativePropertyDeleter)
    (v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Boolean> &);

static
void PropertyQueryCallbackWrapper(
    v8::Local<v8::Name> property
  , const v8::PropertyCallbackInfo<v8::Integer> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Integer>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyQueryCallback callback = reinterpret_cast<PropertyQueryCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyQueryIndex)
              .As<v8::External>()->Value()));
  callback(property.As<v8::String>(), cbinfo);
}

typedef void (*NativePropertyQuery)
    (v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Integer> &);
#else
static
void PropertyGetterCallbackWrapper(
    v8::Local<v8::String> property
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyGetterCallback callback = reinterpret_cast<PropertyGetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyGetterIndex)
              .As<v8::External>()->Value()));
  callback(property, cbinfo);
}

typedef void (*NativePropertyGetter)
    (v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &);

static
void PropertySetterCallbackWrapper(
    v8::Local<v8::String> property
  , v8::Local<v8::Value> value
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertySetterCallback callback = reinterpret_cast<PropertySetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertySetterIndex)
              .As<v8::External>()->Value()));
  callback(property, value, cbinfo);
}

typedef void (*NativePropertySetter)(
    v8::Local<v8::String>
  , v8::Local<v8::Value>
  , const v8::PropertyCallbackInfo<v8::Value> &);

static
void PropertyEnumeratorCallbackWrapper(
    const v8::PropertyCallbackInfo<v8::Array> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Array>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyEnumeratorCallback callback =
      reinterpret_cast<PropertyEnumeratorCallback>(reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyEnumeratorIndex)
              .As<v8::External>()->Value()));
  callback(cbinfo);
}

typedef void (*NativePropertyEnumerator)
    (const v8::PropertyCallbackInfo<v8::Array> &);

static
void PropertyDeleterCallbackWrapper(
    v8::Local<v8::String> property
  , const v8::PropertyCallbackInfo<v8::Boolean> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Boolean>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyDeleterCallback callback = reinterpret_cast<PropertyDeleterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyDeleterIndex)
              .As<v8::External>()->Value()));
  callback(property, cbinfo);
}

typedef void (NativePropertyDeleter)
    (v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Boolean> &);

static
void PropertyQueryCallbackWrapper(
    v8::Local<v8::String> property
  , const v8::PropertyCallbackInfo<v8::Integer> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Integer>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  PropertyQueryCallback callback = reinterpret_cast<PropertyQueryCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kPropertyQueryIndex)
              .As<v8::External>()->Value()));
  callback(property, cbinfo);
}

typedef void (*NativePropertyQuery)
    (v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Integer> &);
#endif

static
void IndexGetterCallbackWrapper(
    uint32_t index, const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  IndexGetterCallback callback = reinterpret_cast<IndexGetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kIndexPropertyGetterIndex)
              .As<v8::External>()->Value()));
  callback(index, cbinfo);
}

typedef void (*NativeIndexGetter)
    (uint32_t, const v8::PropertyCallbackInfo<v8::Value> &);

static
void IndexSetterCallbackWrapper(
    uint32_t index
  , v8::Local<v8::Value> value
  , const v8::PropertyCallbackInfo<v8::Value> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Value>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  IndexSetterCallback callback = reinterpret_cast<IndexSetterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kIndexPropertySetterIndex)
              .As<v8::External>()->Value()));
  callback(index, value, cbinfo);
}

typedef void (*NativeIndexSetter)(
    uint32_t
  , v8::Local<v8::Value>
  , const v8::PropertyCallbackInfo<v8::Value> &);

static
void IndexEnumeratorCallbackWrapper(
    const v8::PropertyCallbackInfo<v8::Array> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Array>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  IndexEnumeratorCallback callback = reinterpret_cast<IndexEnumeratorCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(
              kIndexPropertyEnumeratorIndex).As<v8::External>()->Value()));
  callback(cbinfo);
}

typedef void (*NativeIndexEnumerator)
    (const v8::PropertyCallbackInfo<v8::Array> &);

static
void IndexDeleterCallbackWrapper(
    uint32_t index, const v8::PropertyCallbackInfo<v8::Boolean> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Boolean>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  IndexDeleterCallback callback = reinterpret_cast<IndexDeleterCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kIndexPropertyDeleterIndex)
              .As<v8::External>()->Value()));
  callback(index, cbinfo);
}

typedef void (*NativeIndexDeleter)
    (uint32_t, const v8::PropertyCallbackInfo<v8::Boolean> &);

static
void IndexQueryCallbackWrapper(
    uint32_t index, const v8::PropertyCallbackInfo<v8::Integer> &info) {
  v8::Local<v8::Object> obj = info.Data().As<v8::Object>();
  PropertyCallbackInfo<v8::Integer>
      cbinfo(info, obj->GetInternalField(kDataIndex));
  IndexQueryCallback callback = reinterpret_cast<IndexQueryCallback>(
      reinterpret_cast<intptr_t>(
          obj->GetInternalField(kIndexPropertyQueryIndex)
              .As<v8::External>()->Value()));
  callback(index, cbinfo);
}

typedef void (*NativeIndexQuery)
    (uint32_t, const v8::PropertyCallbackInfo<v8::Integer> &);
}  // end of namespace imp

#endif  // NAN_CALLBACKS_12_INL_H_
