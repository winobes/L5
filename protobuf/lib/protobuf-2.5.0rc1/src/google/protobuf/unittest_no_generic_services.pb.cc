// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_no_generic_services.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "google/protobuf/unittest_no_generic_services.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace google {
namespace protobuf {
namespace no_generic_services_test {

namespace {

const ::google::protobuf::Descriptor* TestMessage_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TestMessage_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* TestEnum_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto() {
  protobuf_AddDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "google/protobuf/unittest_no_generic_services.proto");
  GOOGLE_CHECK(file != NULL);
  TestMessage_descriptor_ = file->message_type(0);
  static const int TestMessage_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMessage, a_),
  };
  TestMessage_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TestMessage_descriptor_,
      TestMessage::default_instance_,
      TestMessage_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMessage, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMessage, _unknown_fields_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TestMessage, _extensions_),
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TestMessage));
  TestEnum_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TestMessage_descriptor_, &TestMessage::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto() {
  delete TestMessage::default_instance_;
  delete TestMessage_reflection_;
}

void protobuf_AddDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n2google/protobuf/unittest_no_generic_se"
    "rvices.proto\022(google.protobuf.no_generic"
    "_services_test\"#\n\013TestMessage\022\t\n\001a\030\001 \001(\005"
    "*\t\010\350\007\020\200\200\200\200\002*\023\n\010TestEnum\022\007\n\003FOO\020\0012\202\001\n\013Tes"
    "tService\022s\n\003Foo\0225.google.protobuf.no_gen"
    "eric_services_test.TestMessage\0325.google."
    "protobuf.no_generic_services_test.TestMe"
    "ssage:N\n\016test_extension\0225.google.protobu"
    "f.no_generic_services_test.TestMessage\030\350"
    "\007 \001(\005", 365);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "google/protobuf/unittest_no_generic_services.proto", &protobuf_RegisterTypes);
  TestMessage::default_instance_ = new TestMessage();
  ::google::protobuf::internal::ExtensionSet::RegisterExtension(
    &::google::protobuf::no_generic_services_test::TestMessage::default_instance(),
    1000, 5, false, false);
  TestMessage::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto {
  StaticDescriptorInitializer_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto() {
    protobuf_AddDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto();
  }
} static_descriptor_initializer_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto_;
const ::google::protobuf::EnumDescriptor* TestEnum_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TestEnum_descriptor_;
}
bool TestEnum_IsValid(int value) {
  switch(value) {
    case 1:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int TestMessage::kAFieldNumber;
#endif  // !_MSC_VER

TestMessage::TestMessage()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void TestMessage::InitAsDefaultInstance() {
}

TestMessage::TestMessage(const TestMessage& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void TestMessage::SharedCtor() {
  _cached_size_ = 0;
  a_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TestMessage::~TestMessage() {
  SharedDtor();
}

void TestMessage::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TestMessage::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TestMessage::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TestMessage_descriptor_;
}

const TestMessage& TestMessage::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto();
  return *default_instance_;
}

TestMessage* TestMessage::default_instance_ = NULL;

TestMessage* TestMessage::New() const {
  return new TestMessage;
}

void TestMessage::Clear() {
  _extensions_.Clear();
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    a_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TestMessage::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 a = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &a_)));
          set_has_a();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        if ((8000u <= tag)) {
          DO_(_extensions_.ParseField(tag, input, default_instance_,
                                      mutable_unknown_fields()));
          continue;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void TestMessage::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // optional int32 a = 1;
  if (has_a()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->a(), output);
  }

  // Extension range [1000, 536870912)
  _extensions_.SerializeWithCachedSizes(
      1000, 536870912, output);

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* TestMessage::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // optional int32 a = 1;
  if (has_a()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->a(), target);
  }

  // Extension range [1000, 536870912)
  target = _extensions_.SerializeWithCachedSizesToArray(
      1000, 536870912, target);

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int TestMessage::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 a = 1;
    if (has_a()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->a());
    }

  }
  total_size += _extensions_.ByteSize();

  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TestMessage::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TestMessage* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TestMessage*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TestMessage::MergeFrom(const TestMessage& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_a()) {
      set_a(from.a());
    }
  }
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TestMessage::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TestMessage::CopyFrom(const TestMessage& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TestMessage::IsInitialized() const {


  if (!_extensions_.IsInitialized()) return false;  return true;
}

void TestMessage::Swap(TestMessage* other) {
  if (other != this) {
    std::swap(a_, other->a_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
    _extensions_.Swap(&other->_extensions_);
  }
}

::google::protobuf::Metadata TestMessage::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TestMessage_descriptor_;
  metadata.reflection = TestMessage_reflection_;
  return metadata;
}

::google::protobuf::internal::ExtensionIdentifier< ::google::protobuf::no_generic_services_test::TestMessage,
    ::google::protobuf::internal::PrimitiveTypeTraits< ::google::protobuf::int32 >, 5, false >
  test_extension(kTestExtensionFieldNumber, 0);

// @@protoc_insertion_point(namespace_scope)

}  // namespace no_generic_services_test
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
