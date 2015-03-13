"""autogenerated by genpy from catec_actions_msgs/DownloadDataResult.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class DownloadDataResult(genpy.Message):
  _md5sum = "f5b68189c823cc97128b89979bd1aea8"
  _type = "catec_actions_msgs/DownloadDataResult"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======
#result definition
uint8   total_images_sent
uint32  total_bytes_sent
uint8   remaining_images
uint32  remaining_bytes

"""
  __slots__ = ['total_images_sent','total_bytes_sent','remaining_images','remaining_bytes']
  _slot_types = ['uint8','uint32','uint8','uint32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       total_images_sent,total_bytes_sent,remaining_images,remaining_bytes

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(DownloadDataResult, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.total_images_sent is None:
        self.total_images_sent = 0
      if self.total_bytes_sent is None:
        self.total_bytes_sent = 0
      if self.remaining_images is None:
        self.remaining_images = 0
      if self.remaining_bytes is None:
        self.remaining_bytes = 0
    else:
      self.total_images_sent = 0
      self.total_bytes_sent = 0
      self.remaining_images = 0
      self.remaining_bytes = 0

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
      buff.write(_struct_BIBI.pack(_x.total_images_sent, _x.total_bytes_sent, _x.remaining_images, _x.remaining_bytes))
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
      end += 10
      (_x.total_images_sent, _x.total_bytes_sent, _x.remaining_images, _x.remaining_bytes,) = _struct_BIBI.unpack(str[start:end])
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
      buff.write(_struct_BIBI.pack(_x.total_images_sent, _x.total_bytes_sent, _x.remaining_images, _x.remaining_bytes))
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
      end += 10
      (_x.total_images_sent, _x.total_bytes_sent, _x.remaining_images, _x.remaining_bytes,) = _struct_BIBI.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_BIBI = struct.Struct("<BIBI")