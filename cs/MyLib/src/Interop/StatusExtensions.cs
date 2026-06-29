using System;
using MyLib.Exceptions;

namespace MyLib.Interop
{
    internal static class StatusExtensions
    {
        internal static void ThrowIfError(this MyLibStatus status)
        {
            if (status == MyLibStatus.Ok)
                return;
            throw ToException(status);
        }

        internal static Exception ToException(this MyLibStatus status)
        {
            return status switch
            {
                MyLibStatus.InvalidHandle => new ObjectDisposedException(null),
                MyLibStatus.InvalidArgument => new ArgumentException("Invalid argument."),
                MyLibStatus.LogicError => new InvalidOperationException("Invalid operation."),
                MyLibStatus.OverflowError => new OverflowException("Integer overflow."),
                MyLibStatus.RangeError => new ArgumentOutOfRangeException("Out of range."),
                MyLibStatus.UnknownError => new MyLibException(status, $"Unknown error!"),
                _ => new MyLibException(status),
            };
        }
    }
}
