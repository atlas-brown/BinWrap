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

//#include <dlfcn.h>
//#include <unistd.h>
//#include <sys/prctl.h>
//#include <sys/mman.h>
//#define _GNU_SOURCE
#include "/home/gchri/BPJS/node-v8.9.4/native_running.h"
//#include <sys/syscall.h>
//#include <stdlib.h>
/*MEM STATS*/
#define PERMS_READ               1U
#define PERMS_WRITE              2U
#define PERMS_EXEC               4U
#define PERMS_SHARED             8U
#define PERMS_PRIVATE           16U

typedef struct mem_address_range mem_address_range;
struct mem_address_range {
    struct mem_address_range    *next;
    void                    *start;
    size_t                   length;
    unsigned long            offset;
    dev_t                    device;
    ino_t                    inode;
    unsigned char            perms;
    char                     name[];
};

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
int node_pkey = 0;

void protec (){
    
    int pid = getpid();
    int status;
    //fprintf(stderr, "PKEY IS %d, disabling write\n",node_pkey);
    status = pkey_set(node_pkey, PKEY_DISABLE_WRITE);
    //fprintf(stderr, "PKEY value %p\n", pkey_get(node_pkey));
//    status = pkey_set(node_pkey, 0);

    //print_mem_info();

}

void node_protec (){

    int pid = getpid();
    int status;
    //fprintf(stderr, "NODE PROTEC: PKEY IS %d\n",node_pkey);
    status = pkey_set(node_pkey, 0);

    mem_address_range *list, *curr;

    list = mem_stats((pid_t)pid);

    for (curr = list; curr != NULL; curr = curr->next){
        if ( (unsigned long) curr->start < 0x555555554000U && curr->perms){
		if (curr->perms & PERMS_EXEC)
                	continue;
		if ((!(curr->perms & PERMS_EXEC)) & (!(curr->perms & PERMS_READ)) & (!(curr->perms & PERMS_WRITE)))
			continue;
		pkey_mprotect(curr->start, curr->length,
                       PROT_WRITE | PROT_READ , node_pkey);
	}
	
    }
    //fprintf(stderr, "PKEY value %p\n", pkey_get(node_pkey));
    //print_mem_info();
}


int node_pkey_set = 0;
int thread_set = 0;

pthread_cond_t wait_for_native_cv;
pthread_cond_t unlock_native_cv;
int run_native = 0;
int run_node = 0;
pthread_mutex_t wait_for_native; 
pthread_mutex_t unlock_native; 
sem_t run_nat, wait_native;
//extern int native_thread_running;

namespace imp {


FunctionCallback inv_callback;
FunctionCallbackInfo<v8::Value> *inv_cbinfo;
v8::Isolate *current_iso;
static void* exec_invoke(void *fcbi){
    int nRet;
    if (!thread_set){ 
    	Dl_info  DlInfo;
	current_iso->Enter();
    	char thname[] = "native_inv\0";
    	prctl(PR_SET_NAME, thname);
	thread_set  = 1;
    }
    //print_mem_info();
    while (1){
//	sem_wait(&wait_native);
	sem_wait(&run_nat);
//	pthread_mutex_lock(&unlock_native);
//	while (run_native == 0){
//		fprintf(stderr, "native waiting\n");
//		pthread_cond_wait(&unlock_native_cv, &unlock_native);
//	}
//	fprintf(stderr, "[Native thread] Lock acquired\n");
//	current_iso->Enter();
	protec();
	current_iso->Enter();
	fprintf(stderr, "[Native thread] native running value is %d\n", get_native_thread_value());
	set_native_thread_value(1);
	fprintf(stderr, "[Native thread] native running value is %d\n", get_native_thread_value());


//   	fprintf(stderr, "[Native thread] Entered iso %d\n", native_thread_running);
 

    	inv_callback(*inv_cbinfo);

    	current_iso->Exit();

//	fprintf(stderr, "[Native Thread] Finished\n");

	run_native = 0;
//	pthread_cond_signal (&wait_for_native_cv);
	
//	pthread_mutex_unlock(&unlock_native);
//	fprintf(stderr, "unlocked for next native call\n");
	sem_post(&wait_native);
	//sem_post(&run_nat);
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
  inv_cbinfo = &cbinfo;
  current_iso = cbinfo.GetIsolate();
  //print_mem_info();
  pthread_t invoke;

  if (node_pkey_set == 0){
	node_pkey = pkey_alloc(0, 0);
    		if (node_pkey == -1)
         		fprintf(stderr, "pkey_alloc\n");
//	fprintf(stderr, "NODE PKEY IS %d\n", node_pkey);
	pkey_set(node_pkey, 0);
	node_protec();
	node_pkey_set = 1;
	/*if (pthread_mutex_init(&wait_for_native, NULL) != 0) { 
        	fprintf(stderr, "\n[NODEMPK] wait_for_native mutex init has failed\n"); 
    	}
	if (pthread_mutex_init(&unlock_native, NULL) != 0) {
        	fprintf(stderr, "\n[NODEMPK] unlock_native mutex init has failed\n");
    	}
	pthread_cond_init(&unlock_native_cv, NULL);
	pthread_cond_init(&wait_for_native_cv, NULL);*/
	sem_init((sem_t*) &run_nat, 0, 0);
	sem_init((sem_t*) &wait_native, 0, 0);
	
	pthread_create (&invoke, NULL, exec_invoke,  NULL);
  }
	sem_post(&run_nat);
	sem_wait(&wait_native);
  
// run_native = 1;
  //fprintf(stderr, "Unlocking native\n");
  /*pthread_cond_signal(&unlock_native_cv);
  //fprintf(stderr, "waiting for native to unlock\n");
  while(run_native != 0)
	  pthread_cond_wait(&wait_for_native_cv, &wait_for_native);
  */
//  pthread_mutex_unlock(&wait_for_native);
  //fprintf(stderr, "unlocked by native\n");
  

  //print_mem_info();
  //fprintf(stderr, "Current Isolate is %p\n", current_iso);
  
  
  //fprintf(stderr, " NODE PKEY value %p\n", pkey_get(node_pkey));
  
  //pthread_join(invoke, &ret);
  //fprintf(stderr, "Function returns \n");

 //  while(!done); 
    
 // callback(cbinfo);
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