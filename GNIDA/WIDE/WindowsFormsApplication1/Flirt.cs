using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace NGNIDA
{
    public class Flirt
    {
        public XmlDocument document = new XmlDocument();
        public string DName;
        public Flirt(string FName)
        {
            DName = FName;
            if (!System.IO.File.Exists(FName))
            {
                XmlTextWriter textWritter = new XmlTextWriter(FName, Encoding.UTF8);
                textWritter.WriteStartDocument();
                textWritter.WriteStartElement("head");
                textWritter.WriteEndElement();
                textWritter.Close();
            }
            document.Load(FName);
            /*
            XmlNode element = document.CreateElement("element");
            document.DocumentElement.AppendChild(element); // указываем родителя
            XmlAttribute attribute = document.CreateAttribute("Name"); // создаём атрибут
            attribute.Value = "cmmStub"; // устанавливаем значение атрибута
            element.Attributes.Append(attribute); // добавляем атрибут

            XmlNode subElement1 = document.CreateElement("result"); // даём имя
            subElement1.InnerText = "void"; // и значение
            element.AppendChild(subElement1); // и указываем кому принадлежит

            XmlNode subElement2 = document.CreateElement("Mask");
            subElement2.InnerText = "FC 6A 00 FF 15 A0 20 40 00 A3 00 10 40 00 FF 15 A8 20 40 00 A3 04 10 40 00 E8 12 00 00 00 50 FF 15 A4 20 40 00";
            element.AppendChild(subElement2);

            XmlNode subElement3 = document.CreateElement("params");
            subElement3.InnerText = "void";
            element.AppendChild(subElement3);
             */ 
            document.Save(DName);
        }
        public void Dispose()
        {
            document.Save(DName);
            GC.SuppressFinalize(this);
        }
    }

}
