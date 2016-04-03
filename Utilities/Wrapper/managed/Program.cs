using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Wrapper;
using System.Reflection;

namespace managed
{
    class Program
    {
        static void Main(string[] args)
        {
            MyClass myWrapper = new MyClass();
            myWrapper.LogCaller("Hello from Managed");

            Type myType = typeof(MyClass);

            MethodInfo[] myArrayMethodInfo = myType.GetMethods(BindingFlags.FlattenHierarchy | BindingFlags.Public | BindingFlags.Instance);
            DisplayMethodInfo("Public", myArrayMethodInfo);

            MethodInfo[] myArrayMethodInfo1 = myType.GetMethods(BindingFlags.FlattenHierarchy | BindingFlags.NonPublic | BindingFlags.Instance);
            DisplayMethodInfo("NonPublic", myArrayMethodInfo1);

            myWrapper.Dispose();
            Console.ReadLine();
        }

        public static void DisplayMethodInfo(string visibility, MethodInfo[] myArrayMethodInfo)
        {
            for (int i = 0; i < myArrayMethodInfo.Length; ++i)
            {
                MethodInfo myMethodInfo = (MethodInfo)myArrayMethodInfo[i];
                Console.WriteLine("\n" + visibility + ": {0}.", myMethodInfo.Name);
            }
        }
    }
}
