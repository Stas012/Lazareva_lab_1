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
            DriveInfo[] drives = DriveInfo.GetDrives(); // Возращает все лог.имена дисков на компе

            foreach (DriveInfo drive in drives) // Предоставляем доступ к дискам
            {
                Console.WriteLine($"Название: {drive.Name}"); // Выводыим название диска и его тип
                Console.WriteLine($"Тип: {drive.DriveType}");
                if (drive.IsReady) // Возращает значение "Готов ли диск?", если да выполняем, если нет, то программа сворачивается
                {
                    Console.WriteLine($"Объем диска: {drive.TotalSize}");
                    Console.WriteLine($"Свободное пространство: {drive.TotalFreeSpace}"); // Вывдоим требуемые данные: объем дисков, свобоная память
                    Console.WriteLine($"Метка: {drive.VolumeLabel}");
                }
                Console.WriteLine(); // Записываем указанные данные
            }
        }
    }


    // Задание 2 работа с текстовым файлом
    class Program_2
    {
        static void Main(string[] args)
        {
            string path = @"E:\Lab_1_OS_2"; // Пишем адрес будущего файла и его папку
            DirectoryInfo dirInfo = new DirectoryInfo(path);  // метод для созлания чего-то нового
            if (!dirInfo.Exists)
            {
                dirInfo.Create(); // Если не нашли нужную папку создаем
            }

            Console.WriteLine("Введите строку для записи в файл:");
            string text = Console.ReadLine(); // Просим у пользователя строку и записываем ее

            using (FileStream fstream = new FileStream(@"E:\Lab_1_OS_2\file_2.txt", FileMode.OpenOrCreate)) // Открываем нужный файл
            {
                byte[] array = System.Text.Encoding.Default.GetBytes(text); // Заносим туда строку
                fstream.Write(array, 0, array.Length);   // Используем наш файл с записанной строкой и сообщаем об этом пользователю
                Console.WriteLine("Текст записан в файл");
            }


            using (FileStream fstream = File.OpenRead(@"E:\Lab_1_OS_2\file_2.txt")) // Открываем наш файл
            {
                byte[] array = new byte[fstream.Length];
                fstream.Read(array, 0, array.Length); // Читаем строку, считывая ее размер
                string textFromFile = System.Text.Encoding.Default.GetString(array); // Закрываем поток
                Console.WriteLine($"Текст из файла: {textFromFile}"); // Выводим нужную информацию
            }

            string surfile = @"E:\Lab_1_OS_2\file_2.txt";
            Console.WriteLine(File.Exists(surfile) ? "Найден": "Такого нет"); // проверяем наличие файла
            {
                File.Delete(surfile);
                Console.WriteLine("Файл удален"); // Удаляем файл
            }


           /* using (FileStream fstream = File.OpenRead(@"E:\Lab_1_OS_2\file_2.txt"))
            {
                string curFile = @"E:\Lab_1_OS_2\file_2.txt";
                Console.WriteLine(File.Exists(curFile) ? "Файл найден" : "Файл не не найден");
                FileInfo fileInf = new FileInfo(@"E:\Lab_1_OS_2\file_2.txt");
                if (fileInf.Exists)
                {
                    fileInf.Delete();
                }
            }*/
            Console.ReadLine();
        }
    }


    // Задание 3 дженсон
    class Person // Создаем класс из которого будем брать наши строки
    {
        public string Name { get; set; }
        public int Age { get; set; }
    }
    class Program_3
    {
        static async Task Main(string[] args)
        {
            using (FileStream fs = new FileStream("file_3.json", FileMode.OpenOrCreate)) // Сохроняем данные
            {
                Person tom = new Person() { Name = "Tom", Age = 35 };
                await JsonSerializer.SerializeAsync<Person>(fs, tom); // Делаем серелезацию файла
                Console.WriteLine("Данные сохрорнены в файл");
            }
        }
        // Не реализованно удаление файла
    }


    // Задание 4 xml
    class User // Корневой элемент внутри, которого хранятся нужные нам данные
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

            xDoc.Load("E:\\Lab_1_OS_2\\file_4.xml"); // Подгружаем наш xml файл
            XmlElement xRoot = xDoc.DocumentElement;
            foreach (XmlElement xnode in xRoot) // Проходимся по всем данным и поочередно их выводим
            {
                User user = new User();
                XmlNode attr = xnode.Attributes.GetNamedItem("Имя: ");
                if (attr != null)
                    user.Name = attr.Value;

                foreach (XmlNode childnode in xnode.ChildNodes)
                {
                    if (childnode.Name == "Компания: ")
                        user.Company = childnode.InnerText;

                    if (childnode.Name == "Возраст: ")
                        user.Age = Int32.Parse(childnode.InnerText);
                }
                users.Add(user);
            }
            foreach (User u in users)
                Console.WriteLine($"{u.Name} ({u.Company}) - {u.Age}"); // Оформляем подобающим образом и заканчиваем работу
            Console.Read();
        }
    }


    // Задание 5
    // Птица тупик не понял как это сделать. Точнее концепт понятен, но реализация не очень
}
