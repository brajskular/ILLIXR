// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sr_input.proto

#ifndef PROTOBUF_INCLUDED_sr_5finput_2eproto
#define PROTOBUF_INCLUDED_sr_5finput_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_sr_5finput_2eproto 

namespace protobuf_sr_5finput_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[3];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_sr_5finput_2eproto
namespace sr_input_proto {
class ImgData;
class ImgDataDefaultTypeInternal;
extern ImgDataDefaultTypeInternal _ImgData_default_instance_;
class Pose;
class PoseDefaultTypeInternal;
extern PoseDefaultTypeInternal _Pose_default_instance_;
class SRData;
class SRDataDefaultTypeInternal;
extern SRDataDefaultTypeInternal _SRData_default_instance_;
}  // namespace sr_input_proto
namespace google {
namespace protobuf {
template<> ::sr_input_proto::ImgData* Arena::CreateMaybeMessage<::sr_input_proto::ImgData>(Arena*);
template<> ::sr_input_proto::Pose* Arena::CreateMaybeMessage<::sr_input_proto::Pose>(Arena*);
template<> ::sr_input_proto::SRData* Arena::CreateMaybeMessage<::sr_input_proto::SRData>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace sr_input_proto {

// ===================================================================

class Pose : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sr_input_proto.Pose) */ {
 public:
  Pose();
  virtual ~Pose();

  Pose(const Pose& from);

  inline Pose& operator=(const Pose& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Pose(Pose&& from) noexcept
    : Pose() {
    *this = ::std::move(from);
  }

  inline Pose& operator=(Pose&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Pose& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Pose* internal_default_instance() {
    return reinterpret_cast<const Pose*>(
               &_Pose_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Pose* other);
  friend void swap(Pose& a, Pose& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Pose* New() const final {
    return CreateMaybeMessage<Pose>(NULL);
  }

  Pose* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Pose>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Pose& from);
  void MergeFrom(const Pose& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Pose* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // double p_x = 1;
  void clear_p_x();
  static const int kPXFieldNumber = 1;
  double p_x() const;
  void set_p_x(double value);

  // double p_y = 2;
  void clear_p_y();
  static const int kPYFieldNumber = 2;
  double p_y() const;
  void set_p_y(double value);

  // double p_z = 3;
  void clear_p_z();
  static const int kPZFieldNumber = 3;
  double p_z() const;
  void set_p_z(double value);

  // double o_x = 4;
  void clear_o_x();
  static const int kOXFieldNumber = 4;
  double o_x() const;
  void set_o_x(double value);

  // double o_y = 5;
  void clear_o_y();
  static const int kOYFieldNumber = 5;
  double o_y() const;
  void set_o_y(double value);

  // double o_z = 6;
  void clear_o_z();
  static const int kOZFieldNumber = 6;
  double o_z() const;
  void set_o_z(double value);

  // double o_w = 7;
  void clear_o_w();
  static const int kOWFieldNumber = 7;
  double o_w() const;
  void set_o_w(double value);

  // @@protoc_insertion_point(class_scope:sr_input_proto.Pose)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  double p_x_;
  double p_y_;
  double p_z_;
  double o_x_;
  double o_y_;
  double o_z_;
  double o_w_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_sr_5finput_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class ImgData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sr_input_proto.ImgData) */ {
 public:
  ImgData();
  virtual ~ImgData();

  ImgData(const ImgData& from);

  inline ImgData& operator=(const ImgData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  ImgData(ImgData&& from) noexcept
    : ImgData() {
    *this = ::std::move(from);
  }

  inline ImgData& operator=(ImgData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const ImgData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ImgData* internal_default_instance() {
    return reinterpret_cast<const ImgData*>(
               &_ImgData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(ImgData* other);
  friend void swap(ImgData& a, ImgData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline ImgData* New() const final {
    return CreateMaybeMessage<ImgData>(NULL);
  }

  ImgData* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<ImgData>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const ImgData& from);
  void MergeFrom(const ImgData& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ImgData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // bytes img_data = 1;
  void clear_img_data();
  static const int kImgDataFieldNumber = 1;
  const ::std::string& img_data() const;
  void set_img_data(const ::std::string& value);
  #if LANG_CXX11
  void set_img_data(::std::string&& value);
  #endif
  void set_img_data(const char* value);
  void set_img_data(const void* value, size_t size);
  ::std::string* mutable_img_data();
  ::std::string* release_img_data();
  void set_allocated_img_data(::std::string* img_data);

  // int32 rows = 2;
  void clear_rows();
  static const int kRowsFieldNumber = 2;
  ::google::protobuf::int32 rows() const;
  void set_rows(::google::protobuf::int32 value);

  // int32 columns = 3;
  void clear_columns();
  static const int kColumnsFieldNumber = 3;
  ::google::protobuf::int32 columns() const;
  void set_columns(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:sr_input_proto.ImgData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr img_data_;
  ::google::protobuf::int32 rows_;
  ::google::protobuf::int32 columns_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_sr_5finput_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class SRData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sr_input_proto.SRData) */ {
 public:
  SRData();
  virtual ~SRData();

  SRData(const SRData& from);

  inline SRData& operator=(const SRData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SRData(SRData&& from) noexcept
    : SRData() {
    *this = ::std::move(from);
  }

  inline SRData& operator=(SRData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const SRData& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SRData* internal_default_instance() {
    return reinterpret_cast<const SRData*>(
               &_SRData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(SRData* other);
  friend void swap(SRData& a, SRData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SRData* New() const final {
    return CreateMaybeMessage<SRData>(NULL);
  }

  SRData* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SRData>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SRData& from);
  void MergeFrom(const SRData& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SRData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .sr_input_proto.Pose input_pose = 1;
  bool has_input_pose() const;
  void clear_input_pose();
  static const int kInputPoseFieldNumber = 1;
  private:
  const ::sr_input_proto::Pose& _internal_input_pose() const;
  public:
  const ::sr_input_proto::Pose& input_pose() const;
  ::sr_input_proto::Pose* release_input_pose();
  ::sr_input_proto::Pose* mutable_input_pose();
  void set_allocated_input_pose(::sr_input_proto::Pose* input_pose);

  // .sr_input_proto.ImgData depth_img_data = 2;
  bool has_depth_img_data() const;
  void clear_depth_img_data();
  static const int kDepthImgDataFieldNumber = 2;
  private:
  const ::sr_input_proto::ImgData& _internal_depth_img_data() const;
  public:
  const ::sr_input_proto::ImgData& depth_img_data() const;
  ::sr_input_proto::ImgData* release_depth_img_data();
  ::sr_input_proto::ImgData* mutable_depth_img_data();
  void set_allocated_depth_img_data(::sr_input_proto::ImgData* depth_img_data);

  // .sr_input_proto.ImgData rgb_img_data = 3;
  bool has_rgb_img_data() const;
  void clear_rgb_img_data();
  static const int kRgbImgDataFieldNumber = 3;
  private:
  const ::sr_input_proto::ImgData& _internal_rgb_img_data() const;
  public:
  const ::sr_input_proto::ImgData& rgb_img_data() const;
  ::sr_input_proto::ImgData* release_rgb_img_data();
  ::sr_input_proto::ImgData* mutable_rgb_img_data();
  void set_allocated_rgb_img_data(::sr_input_proto::ImgData* rgb_img_data);

  // @@protoc_insertion_point(class_scope:sr_input_proto.SRData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::sr_input_proto::Pose* input_pose_;
  ::sr_input_proto::ImgData* depth_img_data_;
  ::sr_input_proto::ImgData* rgb_img_data_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_sr_5finput_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Pose

// double p_x = 1;
inline void Pose::clear_p_x() {
  p_x_ = 0;
}
inline double Pose::p_x() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.p_x)
  return p_x_;
}
inline void Pose::set_p_x(double value) {
  
  p_x_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.p_x)
}

// double p_y = 2;
inline void Pose::clear_p_y() {
  p_y_ = 0;
}
inline double Pose::p_y() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.p_y)
  return p_y_;
}
inline void Pose::set_p_y(double value) {
  
  p_y_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.p_y)
}

// double p_z = 3;
inline void Pose::clear_p_z() {
  p_z_ = 0;
}
inline double Pose::p_z() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.p_z)
  return p_z_;
}
inline void Pose::set_p_z(double value) {
  
  p_z_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.p_z)
}

// double o_x = 4;
inline void Pose::clear_o_x() {
  o_x_ = 0;
}
inline double Pose::o_x() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.o_x)
  return o_x_;
}
inline void Pose::set_o_x(double value) {
  
  o_x_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.o_x)
}

// double o_y = 5;
inline void Pose::clear_o_y() {
  o_y_ = 0;
}
inline double Pose::o_y() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.o_y)
  return o_y_;
}
inline void Pose::set_o_y(double value) {
  
  o_y_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.o_y)
}

// double o_z = 6;
inline void Pose::clear_o_z() {
  o_z_ = 0;
}
inline double Pose::o_z() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.o_z)
  return o_z_;
}
inline void Pose::set_o_z(double value) {
  
  o_z_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.o_z)
}

// double o_w = 7;
inline void Pose::clear_o_w() {
  o_w_ = 0;
}
inline double Pose::o_w() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.Pose.o_w)
  return o_w_;
}
inline void Pose::set_o_w(double value) {
  
  o_w_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.Pose.o_w)
}

// -------------------------------------------------------------------

// ImgData

// bytes img_data = 1;
inline void ImgData::clear_img_data() {
  img_data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ImgData::img_data() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.ImgData.img_data)
  return img_data_.GetNoArena();
}
inline void ImgData::set_img_data(const ::std::string& value) {
  
  img_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:sr_input_proto.ImgData.img_data)
}
#if LANG_CXX11
inline void ImgData::set_img_data(::std::string&& value) {
  
  img_data_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:sr_input_proto.ImgData.img_data)
}
#endif
inline void ImgData::set_img_data(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  img_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:sr_input_proto.ImgData.img_data)
}
inline void ImgData::set_img_data(const void* value, size_t size) {
  
  img_data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:sr_input_proto.ImgData.img_data)
}
inline ::std::string* ImgData::mutable_img_data() {
  
  // @@protoc_insertion_point(field_mutable:sr_input_proto.ImgData.img_data)
  return img_data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ImgData::release_img_data() {
  // @@protoc_insertion_point(field_release:sr_input_proto.ImgData.img_data)
  
  return img_data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ImgData::set_allocated_img_data(::std::string* img_data) {
  if (img_data != NULL) {
    
  } else {
    
  }
  img_data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), img_data);
  // @@protoc_insertion_point(field_set_allocated:sr_input_proto.ImgData.img_data)
}

// int32 rows = 2;
inline void ImgData::clear_rows() {
  rows_ = 0;
}
inline ::google::protobuf::int32 ImgData::rows() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.ImgData.rows)
  return rows_;
}
inline void ImgData::set_rows(::google::protobuf::int32 value) {
  
  rows_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.ImgData.rows)
}

// int32 columns = 3;
inline void ImgData::clear_columns() {
  columns_ = 0;
}
inline ::google::protobuf::int32 ImgData::columns() const {
  // @@protoc_insertion_point(field_get:sr_input_proto.ImgData.columns)
  return columns_;
}
inline void ImgData::set_columns(::google::protobuf::int32 value) {
  
  columns_ = value;
  // @@protoc_insertion_point(field_set:sr_input_proto.ImgData.columns)
}

// -------------------------------------------------------------------

// SRData

// .sr_input_proto.Pose input_pose = 1;
inline bool SRData::has_input_pose() const {
  return this != internal_default_instance() && input_pose_ != NULL;
}
inline void SRData::clear_input_pose() {
  if (GetArenaNoVirtual() == NULL && input_pose_ != NULL) {
    delete input_pose_;
  }
  input_pose_ = NULL;
}
inline const ::sr_input_proto::Pose& SRData::_internal_input_pose() const {
  return *input_pose_;
}
inline const ::sr_input_proto::Pose& SRData::input_pose() const {
  const ::sr_input_proto::Pose* p = input_pose_;
  // @@protoc_insertion_point(field_get:sr_input_proto.SRData.input_pose)
  return p != NULL ? *p : *reinterpret_cast<const ::sr_input_proto::Pose*>(
      &::sr_input_proto::_Pose_default_instance_);
}
inline ::sr_input_proto::Pose* SRData::release_input_pose() {
  // @@protoc_insertion_point(field_release:sr_input_proto.SRData.input_pose)
  
  ::sr_input_proto::Pose* temp = input_pose_;
  input_pose_ = NULL;
  return temp;
}
inline ::sr_input_proto::Pose* SRData::mutable_input_pose() {
  
  if (input_pose_ == NULL) {
    auto* p = CreateMaybeMessage<::sr_input_proto::Pose>(GetArenaNoVirtual());
    input_pose_ = p;
  }
  // @@protoc_insertion_point(field_mutable:sr_input_proto.SRData.input_pose)
  return input_pose_;
}
inline void SRData::set_allocated_input_pose(::sr_input_proto::Pose* input_pose) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete input_pose_;
  }
  if (input_pose) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      input_pose = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, input_pose, submessage_arena);
    }
    
  } else {
    
  }
  input_pose_ = input_pose;
  // @@protoc_insertion_point(field_set_allocated:sr_input_proto.SRData.input_pose)
}

// .sr_input_proto.ImgData depth_img_data = 2;
inline bool SRData::has_depth_img_data() const {
  return this != internal_default_instance() && depth_img_data_ != NULL;
}
inline void SRData::clear_depth_img_data() {
  if (GetArenaNoVirtual() == NULL && depth_img_data_ != NULL) {
    delete depth_img_data_;
  }
  depth_img_data_ = NULL;
}
inline const ::sr_input_proto::ImgData& SRData::_internal_depth_img_data() const {
  return *depth_img_data_;
}
inline const ::sr_input_proto::ImgData& SRData::depth_img_data() const {
  const ::sr_input_proto::ImgData* p = depth_img_data_;
  // @@protoc_insertion_point(field_get:sr_input_proto.SRData.depth_img_data)
  return p != NULL ? *p : *reinterpret_cast<const ::sr_input_proto::ImgData*>(
      &::sr_input_proto::_ImgData_default_instance_);
}
inline ::sr_input_proto::ImgData* SRData::release_depth_img_data() {
  // @@protoc_insertion_point(field_release:sr_input_proto.SRData.depth_img_data)
  
  ::sr_input_proto::ImgData* temp = depth_img_data_;
  depth_img_data_ = NULL;
  return temp;
}
inline ::sr_input_proto::ImgData* SRData::mutable_depth_img_data() {
  
  if (depth_img_data_ == NULL) {
    auto* p = CreateMaybeMessage<::sr_input_proto::ImgData>(GetArenaNoVirtual());
    depth_img_data_ = p;
  }
  // @@protoc_insertion_point(field_mutable:sr_input_proto.SRData.depth_img_data)
  return depth_img_data_;
}
inline void SRData::set_allocated_depth_img_data(::sr_input_proto::ImgData* depth_img_data) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete depth_img_data_;
  }
  if (depth_img_data) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      depth_img_data = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, depth_img_data, submessage_arena);
    }
    
  } else {
    
  }
  depth_img_data_ = depth_img_data;
  // @@protoc_insertion_point(field_set_allocated:sr_input_proto.SRData.depth_img_data)
}

// .sr_input_proto.ImgData rgb_img_data = 3;
inline bool SRData::has_rgb_img_data() const {
  return this != internal_default_instance() && rgb_img_data_ != NULL;
}
inline void SRData::clear_rgb_img_data() {
  if (GetArenaNoVirtual() == NULL && rgb_img_data_ != NULL) {
    delete rgb_img_data_;
  }
  rgb_img_data_ = NULL;
}
inline const ::sr_input_proto::ImgData& SRData::_internal_rgb_img_data() const {
  return *rgb_img_data_;
}
inline const ::sr_input_proto::ImgData& SRData::rgb_img_data() const {
  const ::sr_input_proto::ImgData* p = rgb_img_data_;
  // @@protoc_insertion_point(field_get:sr_input_proto.SRData.rgb_img_data)
  return p != NULL ? *p : *reinterpret_cast<const ::sr_input_proto::ImgData*>(
      &::sr_input_proto::_ImgData_default_instance_);
}
inline ::sr_input_proto::ImgData* SRData::release_rgb_img_data() {
  // @@protoc_insertion_point(field_release:sr_input_proto.SRData.rgb_img_data)
  
  ::sr_input_proto::ImgData* temp = rgb_img_data_;
  rgb_img_data_ = NULL;
  return temp;
}
inline ::sr_input_proto::ImgData* SRData::mutable_rgb_img_data() {
  
  if (rgb_img_data_ == NULL) {
    auto* p = CreateMaybeMessage<::sr_input_proto::ImgData>(GetArenaNoVirtual());
    rgb_img_data_ = p;
  }
  // @@protoc_insertion_point(field_mutable:sr_input_proto.SRData.rgb_img_data)
  return rgb_img_data_;
}
inline void SRData::set_allocated_rgb_img_data(::sr_input_proto::ImgData* rgb_img_data) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete rgb_img_data_;
  }
  if (rgb_img_data) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      rgb_img_data = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, rgb_img_data, submessage_arena);
    }
    
  } else {
    
  }
  rgb_img_data_ = rgb_img_data;
  // @@protoc_insertion_point(field_set_allocated:sr_input_proto.SRData.rgb_img_data)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace sr_input_proto

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_sr_5finput_2eproto
