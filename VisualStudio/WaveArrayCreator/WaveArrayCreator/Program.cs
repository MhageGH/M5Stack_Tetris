using System;
using System.IO;

namespace WaveArrayCreator
{
    class Program
    {
        static void Main(string[] args)
        {
            byte[] data;
            using (var fs = new FileStream("tesris8.wav", FileMode.Open))
            {
                data = new byte[fs.Length];
                fs.Read(data, 0, (int)fs.Length);
            }
            using (var writer = new StreamWriter("tetris_wav.h"))
            {
                writer.Write("const byte tetris_wav[] = { " + Environment.NewLine);
                for (int i = 0; i < data.Length; ++i)
                {
                    writer.Write("0x" + data[i].ToString("X2")
                        + (i != (data.Length - 1) ? ", " : "")
                        + (i % 16 == 15 ? Environment.NewLine : ""));
                }
                writer.Write(" };");
            }
        }
    }
}
