# Lazareva_lab_1
Лабораторная работа 1 по ОС

using System;
using System.IO;
using System.Threading.Tasks;
using System.IO.Compression;
using System.Text.Json;
using System.Xml;

namespace HelloApp
{
    // Задание 1 инфо о компе
    class Program_1
    {
        static void Main(string[] args, object Internal)
        {
            DriveInfo[] drives = DriveInfo.GetDrives();

            foreach (DriveInfo drive in drives)
            {
                Console.WriteLine($"Название: {drive.Name}");
                Console.WriteLine($"Тип: {drive.DriveType}");
                if (drive.IsReady)
                {
                    Console.WriteLine($"Объем диска: {drive.TotalSize}");
                    Console.WriteLine($"Свободное пространство: {drive.TotalFreeSpace}");
                    Console.WriteLine($"Метка: {drive.VolumeLabel}");
                }
                Console.WriteLine();
            }
        }
    }


    // Задание 2 работа с текстовым файлом
    class Program_2
    {
        static void Main(string[] args)
        {
            string path = @"E:\Lab_1_OS_2"; // Пишем адрес будущего файла
            DirectoryInfo dirInfo = new DirectoryInfo(path);
            if (!dirInfo.Exists)
            {
                dirInfo.Create(); // Если не нашли нужную папку создаем
            }

            Console.WriteLine("Введите строку для записи в файл:");
            string text = Console.ReadLine(); // Просим у пользователя строку и записываем ее

            using (FileStream fstream = new FileStream(@"E:\Lab_1_OS_2\file_2.txt", FileMode.OpenOrCreate))
            {
                byte[] array = System.Text.Encoding.Default.GetBytes(text);
                fstream.Write(array, 0, array.Length);   // Используем наш файл с записанной строкой и сообщаем об этом пользователю
                Console.WriteLine("Текст записан в файл");
            }


            using (FileStream fstream = File.OpenRead(@"E:\Lab_1_OS_2\file_2.txt")) // Открываем наш файл
            {
                byte[] array = new byte[fstream.Length];
                fstream.Read(array, 0, array.Length); // Выводим строку, которая лежит внутри
                string textFromFile = System.Text.Encoding.Default.GetString(array);
                Console.WriteLine($"Текст из файла: {textFromFile}");
            }

            // Нужно закрыть файл, после снова открыть и удалить данные. Есть только удаление, которое не работает


            using (FileStream fstream = File.OpenRead(@"E:\Lab_1_OS_2\file_2.txt"))
            {
                string curFile = @"E:\Lab_1_OS_2\file_2.txt";
                Console.WriteLine(File.Exists(curFile) ? "Файл найден" : "Файл не не найден");
                FileInfo fileInf = new FileInfo(@"E:\Lab_1_OS_2\file_2.txt");
                if (fileInf.Exists)
                {
                    fileInf.Delete();
                }
            }
            Console.ReadLine();
        }
    }


    // Задание 3 дженсон
    class Person
    {
        public string Name { get; set; }
        public int Age { get; set; }
    }
    class Program_3
    {
        static async Task Main(string[] args)
        {
            // сохранение данных
            using (FileStream fs = new FileStream("file_3.json", FileMode.OpenOrCreate))
            {
                Person tom = new Person() { Name = "Tom", Age = 35 };
                await JsonSerializer.SerializeAsync<Person>(fs, tom);
                Console.WriteLine("Data has been saved to file");
            }
        }
    }


    // Задание 4
    class User
    {
        public string Name { get; set; }
        public int Age { get; set; }
        public string Company { get; set; }
    }
    class Program_4
    {
        static void Main(string[] args)
        {
            List<User> users = new List<User>();

            XmlDocument xDoc = new XmlDocument();
            xDoc.Load("E:\\Lab_1_OS_2\\file_4.xml");
            XmlElement xRoot = xDoc.DocumentElement;
            foreach (XmlElement xnode in xRoot)
            {
                User user = new User();
                XmlNode attr = xnode.Attributes.GetNamedItem("name");
                if (attr != null)
                    user.Name = attr.Value;

                foreach (XmlNode childnode in xnode.ChildNodes)
                {
                    if (childnode.Name == "company")
                        user.Company = childnode.InnerText;

                    if (childnode.Name == "age")
                        user.Age = Int32.Parse(childnode.InnerText);
                }
                users.Add(user);
            }
            foreach (User u in users)
                Console.WriteLine($"{u.Name} ({u.Company}) - {u.Age}");
            Console.Read();
        }
    }


    // Задание 5
    // На этом мои полномочия все
}
