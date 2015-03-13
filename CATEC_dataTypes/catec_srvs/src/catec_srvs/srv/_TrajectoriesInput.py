"""autogenerated by genpy from catec_srvs/TrajectoriesInputRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import catec_msgs.msg

class TrajectoriesInputRequest(genpy.Message):
  _md5sum = "c58a424fc11de3017bb73872f54a4f43"
  _type = "catec_srvs/TrajectoriesInputRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """catec_msgs/MultiUAVCollision trayectories

================================================================================
MSG: catec_msgs/MultiUAVCollision
TimePriorityCollisionPoint[] trayectories

================================================================================
MSG: catec_msgs/TimePriorityCollisionPoint
float64 x
float64 y
float64 z
uint8 priority
uint32 time

"""
  __slots__ = ['trayectories']
  _slot_types = ['catec_msgs/MultiUAVCollision']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       trayectories

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TrajectoriesInputRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.trayectories is None:
        self.trayectories = catec_msgs.msg.MultiUAVCollision()
    else:
      self.trayectories = catec_msgs.msg.MultiUAVCollision()

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
      length = len(self.trayectories.trayectories)
      buff.write(_struct_I.pack(length))
      for val1 in self.trayectories.trayectories:
        _x = val1
        buff.write(_struct_3dBI.pack(_x.x, _x.y, _x.z, _x.priority, _x.time))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.trayectories is None:
        self.trayectories = catec_msgs.msg.MultiUAVCollision()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.trayectories.trayectories = []
      for i in range(0, length):
        val1 = catec_msgs.msg.TimePriorityCollisionPoint()
        _x = val1
        start = end
        end += 29
        (_x.x, _x.y, _x.z, _x.priority, _x.time,) = _struct_3dBI.unpack(str[start:end])
        self.trayectories.trayectories.append(val1)
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
      length = len(self.trayectories.trayectories)
      buff.write(_struct_I.pack(length))
      for val1 in self.trayectories.trayectories:
        _x = val1
        buff.write(_struct_3dBI.pack(_x.x, _x.y, _x.z, _x.priority, _x.time))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.trayectories is None:
        self.trayectories = catec_msgs.msg.MultiUAVCollision()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.trayectories.trayectories = []
      for i in range(0, length):
        val1 = catec_msgs.msg.TimePriorityCollisionPoint()
        _x = val1
        start = end
        end += 29
        (_x.x, _x.y, _x.z, _x.priority, _x.time,) = _struct_3dBI.unpack(str[start:end])
        self.trayectories.trayectories.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3dBI = struct.Struct("<3dBI")
"""autogenerated by genpy from catec_srvs/TrajectoriesInputResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class TrajectoriesInputResponse(genpy.Message):
  _md5sum = "d41d8cd98f00b204e9800998ecf8427e"
  _type = "catec_srvs/TrajectoriesInputResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """


"""
  __slots__ = []
  _slot_types = []

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(TrajectoriesInputResponse, self).__init__(*args, **kwds)

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
      pass
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
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
      pass
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
class TrajectoriesInput(object):
  _type          = 'catec_srvs/TrajectoriesInput'
  _md5sum = 'c58a424fc11de3017bb73872f54a4f43'
  _request_class  = TrajectoriesInputRequest
  _response_class = TrajectoriesInputResponse
