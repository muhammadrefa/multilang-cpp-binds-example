using System;
using MyLib.Interop;

namespace MyLib.Exceptions
{
    public class MyLibException : Exception
    {
        public MyLibStatus Status { get; }

        public MyLibException(MyLibStatus status) : base($"Native operation failed with status '{status}'.")
        {
            Status = status;
        }

        public MyLibException(MyLibStatus status, string message) : base(message)
        {
            Status = status;
        }

        public MyLibException(MyLibStatus status, string message, Exception inner) : base(message, inner)
        {
            Status = status;
        }
    }
}
