// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_V8THREADS_H_
#define V8_V8THREADS_H_

#include "src/isolate.h"
//#include <sys/mman.h>
namespace v8 {
namespace internal {

class RootVisitor;
class ThreadLocalTop;

class ThreadState {
 public:
  // Returns NULL after the last one.
  ThreadState* Next();

  enum List {FREE_LIST, IN_USE_LIST};

  void LinkInto(List list);
  void Unlink();

  // Id of thread.
  void set_id(ThreadId id) { id_ = id; }
  ThreadId id() { return id_; }

  // Should the thread be terminated when it is restored?
  bool terminate_on_restore() { return terminate_on_restore_; }
  void set_terminate_on_restore(bool terminate_on_restore) {
    terminate_on_restore_ = terminate_on_restore;
  }

  // Get data area for archiving a thread.
  char* data() { return data_; }

 private:
  explicit ThreadState(ThreadManager* thread_manager);
  ~ThreadState();

  void AllocateSpace();

  ThreadId id_;
  bool terminate_on_restore_;
  char* data_;
  ThreadState* next_;
  ThreadState* previous_;

  ThreadManager* thread_manager_;

  friend class ThreadManager;
};

class ThreadVisitor {
 public:
  // ThreadLocalTop may be only available during this call.
  virtual void VisitThread(Isolate* isolate, ThreadLocalTop* top) = 0;

 protected:
  virtual ~ThreadVisitor() {}
};

//#include <sys/mman.h>

class ThreadManager {
 public:
  void Lock();
  void Unlock();

  void ArchiveThread();
  bool RestoreThread();
  void FreeThreadResources();
  bool IsArchived();

  void Iterate(RootVisitor* v);
  void IterateArchivedThreads(ThreadVisitor* v);
  bool IsLockedByCurrentThread() {

	  unsigned int result, pkval1, pkval2;

        __asm__ volatile (".byte 0x0f, 0x01, 0xee"
                    : "=a" (result) : "c" (0) : "rdx");
        pkval1 = (result >> 2) & 3;
        pkval2 = (result >> 4) & 3;
//    fprintf(stderr, "LockedByCurrentThread is %d %d\n", pkval1, pkval2);
    if ((pkval1 > 1 || pkval1 == 0) || (pkval2 > 1 || pkval2 == 0))
            return true;

	  
	  /*    char thread_name[16];
    pthread_t current = pthread_self();
    const int getname_rv = pthread_getname_np(current, thread_name, 16);
    // NATIVEMODULE SANDBOX
    if (pkey_get(1) > 2)
	    return true;
    if (getname_rv == 0){
        if (strcmp("native_inv", thread_name) == 0)
            return true;
    }*/
    return mutex_owner_.Equals(ThreadId::Current());
  }

  ThreadId CurrentId();

  void TerminateExecution(ThreadId thread_id);

  // Iterate over in-use states.
  ThreadState* FirstThreadStateInUse();
  ThreadState* GetFreeThreadState();

 private:
  ThreadManager();
  ~ThreadManager();

  void DeleteThreadStateList(ThreadState* anchor);

  void EagerlyArchiveThread();

  base::Mutex mutex_;
  ThreadId mutex_owner_;
  ThreadId lazily_archived_thread_;
  ThreadState* lazily_archived_thread_state_;

  // In the following two lists there is always at least one object on the list.
  // The first object is a flying anchor that is only there to simplify linking
  // and unlinking.
  // Head of linked list of free states.
  ThreadState* free_anchor_;
  // Head of linked list of states in use.
  ThreadState* in_use_anchor_;

  Isolate* isolate_;

  friend class Isolate;
  friend class ThreadState;
};


}  // namespace internal
}  // namespace v8

#endif  // V8_V8THREADS_H_
