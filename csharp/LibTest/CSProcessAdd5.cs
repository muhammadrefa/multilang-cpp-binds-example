using System;
using System.ComponentModel.Design;
using System.Text;
using MyLib.Interop;
using MyLib.Interop.Handles;

namespace MyLib
{
    public class CSProcessAdd5 : NumberProcessorProxy
    {
        public CSProcessAdd5() : base()
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
    }
}
