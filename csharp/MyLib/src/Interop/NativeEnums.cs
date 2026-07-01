namespace MyLib.Interop
{
    public enum MyLibStatus
    {
        Ok = 0,

        UnknownError = -1,
        InvalidHandle = -2,
        InvalidArgument = -3,

        LogicError = -11,
        OverflowError = -12,
        RangeError = -13,

        BufferTooSmall = -51
    }
}
