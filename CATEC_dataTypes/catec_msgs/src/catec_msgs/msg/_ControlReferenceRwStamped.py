"""autogenerated by genpy from catec_msgs/ControlReferenceRwStamped.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg
import std_msgs.msg

class ControlReferenceRwStamped(genpy.Message):
  _md5sum = "30b960a85e554e35656bed95e8e455a0"
  _type = "catec_msgs/ControlReferenceRwStamped"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
ControlReferenceRw c_reference_rw
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.secs: seconds (stamp_secs) since epoch
# * stamp.nsecs: nanoseconds since stamp_secs
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: catec_msgs/ControlReferenceRw
Position position
float64 cruise
float64 heading
================================================================================
MSG: catec_msgs/Position
float64 x
float64 y
float64 z
"""
  __slots__ = ['header','c_reference_rw']
  _slot_types = ['std_msgs/Header','catec_msgs/ControlReferenceRw']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       header,c_reference_rw

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ControlReferenceRwStamped, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.c_reference_rw is None:
        self.c_reference_rw = catec_msgs.msg.ControlReferenceRw()
    else:
      self.header = std_msgs.msg.Header()
      self.c_reference_rw = catec_msgs.msg.ControlReferenceRw()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_5d.pack(_x.c_reference_rw.position.x, _x.c_reference_rw.position.y, _x.c_reference_rw.position.z, _x.c_reference_rw.cruise, _x.c_reference_rw.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.c_reference_rw is None:
        self.c_reference_rw = catec_msgs.msg.ControlReferenceRw()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 40
      (_x.c_reference_rw.position.x, _x.c_reference_rw.position.y, _x.c_reference_rw.position.z, _x.c_reference_rw.cruise, _x.c_reference_rw.heading,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_5d.pack(_x.c_reference_rw.position.x, _x.c_reference_rw.position.y, _x.c_reference_rw.position.z, _x.c_reference_rw.cruise, _x.c_reference_rw.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg.Header()
      if self.c_reference_rw is None:
        self.c_reference_rw = catec_msgs.msg.ControlReferenceRw()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.header.frame_id = str[start:end].decode('utf-8')
      else:
        self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 40
      (_x.c_reference_rw.position.x, _x.c_reference_rw.position.y, _x.c_reference_rw.position.z, _x.c_reference_rw.cruise, _x.c_reference_rw.heading,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_5d = struct.Struct("<5d")
_struct_3I = struct.Struct("<3I")