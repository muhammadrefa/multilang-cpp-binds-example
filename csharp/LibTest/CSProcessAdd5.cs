using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class CSProcessAdd5 : NumberProcessorProxy<CSProcessAdd5>
    {
        public CSProcessAdd5() : base()
        {
        }

        // for downcasting
        protected internal CSProcessAdd5(IntPtr handle) : base(handle)
        {
        }

        public override void Process()
        {
            int number = GetNumber();
            number += 5;
            SetNumber(number);
        }

        public override void PrintNumber()
        {
            Console.Write("CS print number -> ");
            base.PrintNumber();
        }

        public void Hello()
        {
            Console.WriteLine("Hello from C#!");
        }
    }
}
