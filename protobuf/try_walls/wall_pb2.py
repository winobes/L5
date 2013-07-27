# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: wall.proto

from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='wall.proto',
  package='',
  serialized_pb='\n\nwall.proto\"\x91\x01\n\x04Wall\x12\x0e\n\x06health\x18\x01 \x01(\x02\x12\x0e\n\x06\x65xists\x18\x02 \x01(\x08\x12\r\n\x05solid\x18\x03 \x01(\x08\x12\x0b\n\x03hot\x18\x04 \x01(\x08\x12\t\n\x01w\x18\x05 \x01(\x02\x12\t\n\x01h\x18\x06 \x01(\x02\x12\t\n\x01\x64\x18\x07 \x01(\x02\x12\x17\n\x03\x65xt\x18\x08 \x01(\x0b\x32\n.Extension\x12\x13\n\x0bsprite_name\x18\t \x01(\t\"2\n\tExtension\x12\x0e\n\x06nverts\x18\x01 \x01(\x05\x12\x15\n\x04vert\x18\x02 \x03(\x0b\x32\x07.Vertex\"\x1e\n\x06Vertex\x12\t\n\x01x\x18\x01 \x01(\x02\x12\t\n\x01y\x18\x02 \x01(\x02')




_WALL = _descriptor.Descriptor(
  name='Wall',
  full_name='Wall',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='health', full_name='Wall.health', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='exists', full_name='Wall.exists', index=1,
      number=2, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='solid', full_name='Wall.solid', index=2,
      number=3, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='hot', full_name='Wall.hot', index=3,
      number=4, type=8, cpp_type=7, label=1,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='w', full_name='Wall.w', index=4,
      number=5, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='h', full_name='Wall.h', index=5,
      number=6, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='d', full_name='Wall.d', index=6,
      number=7, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ext', full_name='Wall.ext', index=7,
      number=8, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sprite_name', full_name='Wall.sprite_name', index=8,
      number=9, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=15,
  serialized_end=160,
)


_EXTENSION = _descriptor.Descriptor(
  name='Extension',
  full_name='Extension',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='nverts', full_name='Extension.nverts', index=0,
      number=1, type=5, cpp_type=1, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='vert', full_name='Extension.vert', index=1,
      number=2, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=162,
  serialized_end=212,
)


_VERTEX = _descriptor.Descriptor(
  name='Vertex',
  full_name='Vertex',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='x', full_name='Vertex.x', index=0,
      number=1, type=2, cpp_type=6, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='y', full_name='Vertex.y', index=1,
      number=2, type=2, cpp_type=6, label=1,
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
  serialized_start=214,
  serialized_end=244,
)

_WALL.fields_by_name['ext'].message_type = _EXTENSION
_EXTENSION.fields_by_name['vert'].message_type = _VERTEX
DESCRIPTOR.message_types_by_name['Wall'] = _WALL
DESCRIPTOR.message_types_by_name['Extension'] = _EXTENSION
DESCRIPTOR.message_types_by_name['Vertex'] = _VERTEX

class Wall(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _WALL

  # @@protoc_insertion_point(class_scope:Wall)

class Extension(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _EXTENSION

  # @@protoc_insertion_point(class_scope:Extension)

class Vertex(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _VERTEX

  # @@protoc_insertion_point(class_scope:Vertex)


# @@protoc_insertion_point(module_scope)