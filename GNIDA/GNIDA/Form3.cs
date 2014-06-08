using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Xml;

namespace GNIDA
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }
        public Flirt flrt;
        public TFunc Func;
        private void Form3_Load(object sender, EventArgs e)
        {
            XmlTextReader reader = new XmlTextReader(flrt.DName);
            reader.ReadToFollowing("Name");
            textBox4.Text = (string)reader.ReadElementContentAs(typeof(string), null);
            reader.ReadToNextSibling("Mask");
            textBox4.Text += (string)reader.ReadElementContentAs(typeof(string), null);
            textBox2.Text = Func.FName;
            Funcs.ReadXml(flrt.DName);
            dataGridView1.DataSource = Funcs;
            dataGridView1.DataMember = "function";
        }
    }
}
