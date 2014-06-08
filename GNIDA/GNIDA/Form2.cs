using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GNIDA
{
    public partial class Form2 : Form
    {
        public string NName;
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Shown(object sender, EventArgs e)
        {
            textBox1.Text = NName; 
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            NName = textBox1.Text;
        }

    }
}
