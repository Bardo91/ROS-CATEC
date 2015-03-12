"""autogenerated by genpy from uav/Data_Header.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Data_Header(genpy.Message):
  _md5sum = "e475a694e3cb9e70aac3eb08dae30d26"
  _type = "uav/Data_Header"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """uint32 seq
float64 stamp
string frame_id
bool status
byte quality
"""
  __slots__ = ['seq','stamp','frame_id','status','quality']
  _slot_types = ['uint32','float64','string','bool','byte']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       seq,stamp,frame_id,status,quality

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Data_Header, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.seq is None:
        self.seq = 0
      if self.stamp is None:
        self.stamp = 0.
      if self.frame_id is None:
        self.frame_id = ''
      if self.status is None:
        self.status = False
      if self.quality is None:
        self.quality = 0
    else:
      self.seq = 0
      self.stamp = 0.
      self.frame_id = ''
      self.status = False
      self.quality = 0

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
      buff.write(_struct_Id.pack(_x.seq, _x.stamp))
      _x = self.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_Bb.pack(_x.status, _x.quality))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 12
      (_x.seq, _x.stamp,) = _struct_Id.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.frame_id = str[start:end].decode('utf-8')
      else:
        self.frame_id = str[start:end]
      _x = self
      start = end
      end += 2
      (_x.status, _x.quality,) = _struct_Bb.unpack(str[start:end])
      self.status = bool(self.status)
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
      buff.write(_struct_Id.pack(_x.seq, _x.stamp))
      _x = self.frame_id
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_Bb.pack(_x.status, _x.quality))
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
      _x = self
      start = end
      end += 12
      (_x.seq, _x.stamp,) = _struct_Id.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.frame_id = str[start:end].decode('utf-8')
      else:
        self.frame_id = str[start:end]
      _x = self
      start = end
      end += 2
      (_x.status, _x.quality,) = _struct_Bb.unpack(str[start:end])
      self.status = bool(self.status)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_Id = struct.Struct("<Id")
_struct_Bb = struct.Struct("<Bb")
