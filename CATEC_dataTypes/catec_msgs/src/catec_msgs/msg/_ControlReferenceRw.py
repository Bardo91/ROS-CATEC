"""autogenerated by genpy from catec_msgs/ControlReferenceRw.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg

class ControlReferenceRw(genpy.Message):
  _md5sum = "f267b6031d79c335f613d206674bda79"
  _type = "catec_msgs/ControlReferenceRw"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """Position position
float64 cruise
float64 heading
================================================================================
MSG: catec_msgs/Position
float64 x
float64 y
float64 z
"""
  __slots__ = ['position','cruise','heading']
  _slot_types = ['catec_msgs/Position','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       position,cruise,heading

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ControlReferenceRw, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.position is None:
        self.position = catec_msgs.msg.Position()
      if self.cruise is None:
        self.cruise = 0.
      if self.heading is None:
        self.heading = 0.
    else:
      self.position = catec_msgs.msg.Position()
      self.cruise = 0.
      self.heading = 0.

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
      buff.write(_struct_5d.pack(_x.position.x, _x.position.y, _x.position.z, _x.cruise, _x.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.position is None:
        self.position = catec_msgs.msg.Position()
      end = 0
      _x = self
      start = end
      end += 40
      (_x.position.x, _x.position.y, _x.position.z, _x.cruise, _x.heading,) = _struct_5d.unpack(str[start:end])
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
      buff.write(_struct_5d.pack(_x.position.x, _x.position.y, _x.position.z, _x.cruise, _x.heading))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.position is None:
        self.position = catec_msgs.msg.Position()
      end = 0
      _x = self
      start = end
      end += 40
      (_x.position.x, _x.position.y, _x.position.z, _x.cruise, _x.heading,) = _struct_5d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_5d = struct.Struct("<5d")
