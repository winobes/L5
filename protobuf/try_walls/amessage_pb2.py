# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: amessage.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='amessage.proto',
  package='',
  serialized_pb='\n\x0e\x61message.proto\" \n\x08\x41Message\x12\t\n\x01\x61\x18\x01 \x02(\x05\x12\t\n\x01\x62\x18\x02 \x01(\x05')




_AMESSAGE = _descriptor.Descriptor(
  name='AMessage',
  full_name='AMessage',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='a', full_name='AMessage.a', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='b', full_name='AMessage.b', index=1,
      number=2, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=18,
  serialized_end=50,
)

DESCRIPTOR.message_types_by_name['AMessage'] = _AMESSAGE

class AMessage(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _AMESSAGE

  # @@protoc_insertion_point(class_scope:AMessage)


# @@protoc_insertion_point(module_scope)