// Generated by gencpp from file test_pkg/JudgeServiceMsgResponse.msg
// DO NOT EDIT!


#ifndef TEST_PKG_MESSAGE_JUDGESERVICEMSGRESPONSE_H
#define TEST_PKG_MESSAGE_JUDGESERVICEMSGRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace test_pkg
{
template <class ContainerAllocator>
struct JudgeServiceMsgResponse_
{
  typedef JudgeServiceMsgResponse_<ContainerAllocator> Type;

  JudgeServiceMsgResponse_()
    : ans(false)  {
    }
  JudgeServiceMsgResponse_(const ContainerAllocator& _alloc)
    : ans(false)  {
  (void)_alloc;
    }



   typedef uint8_t _ans_type;
  _ans_type ans;





  typedef boost::shared_ptr< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> const> ConstPtr;

}; // struct JudgeServiceMsgResponse_

typedef ::test_pkg::JudgeServiceMsgResponse_<std::allocator<void> > JudgeServiceMsgResponse;

typedef boost::shared_ptr< ::test_pkg::JudgeServiceMsgResponse > JudgeServiceMsgResponsePtr;
typedef boost::shared_ptr< ::test_pkg::JudgeServiceMsgResponse const> JudgeServiceMsgResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace test_pkg

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/melodic/share/std_msgs/cmake/../msg'], 'test_pkg': ['/home/lhz/tutorial_2019/tasks/week3/test_project/src/test_pkg/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "4c4b05f69b62d4641eb7409883f6359d";
  }

  static const char* value(const ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x4c4b05f69b62d464ULL;
  static const uint64_t static_value2 = 0x1eb7409883f6359dULL;
};

template<class ContainerAllocator>
struct DataType< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "test_pkg/JudgeServiceMsgResponse";
  }

  static const char* value(const ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ans\n"
"\n"
;
  }

  static const char* value(const ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ans);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct JudgeServiceMsgResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::test_pkg::JudgeServiceMsgResponse_<ContainerAllocator>& v)
  {
    s << indent << "ans: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ans);
  }
};

} // namespace message_operations
} // namespace ros

#endif // TEST_PKG_MESSAGE_JUDGESERVICEMSGRESPONSE_H