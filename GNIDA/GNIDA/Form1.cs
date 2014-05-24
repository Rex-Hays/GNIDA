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
using TUP.AsmResolver;
using Be.Windows.Forms;
using FastColoredTextBoxNS;

namespace GNIDA
{
    public partial class MainForm : Form
    {
        GNIDA MyGNIDA;
        DynamicFileByteProvider dynamicFileByteProvider;
        TextStyle blueStyle = new TextStyle(Brushes.Blue, null, FontStyle.Regular);
        public MainForm()
        {
            InitializeComponent();
        }

        private void openToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        delegate void InsTextCallback(string text);
        private void InsText(string text)
        {
            fastColoredTextBox1.Navigate(8);
            fastColoredTextBox1.InsertText(text);
        }

        public void AddVarEvent1(object sender, TVar Var)
        {
            if (this.fastColoredTextBox1.InvokeRequired)
            {
                try
                {
                    InsTextCallback d = new InsTextCallback(InsText);
                    this.Invoke(d, new object[] { Var.ToStr() + ";\n" });
                }
                catch (System.ObjectDisposedException) { }
            }
            else
            {
                AppendText(Var.FName);
            }

            /*
            fastColoredTextBox1.Navigate(4);
            //fastColoredTextBox1.Lines[4] += Var.FName;
            fastColoredTextBox1.InsertText(Var.FName + ";\n");
             */
        }
        public void AddFuncEvent1(object sender, TFunc func)
        {
            ListViewItem itm1 = new ListViewItem();
            itm1.Text = func.FName;
            itm1.Tag = func;
            listView3.Items.Add(itm1);
            if (func.type == 2)//Export
            {
                ListViewItem itm = new ListViewItem();
                itm.Text = func.FName;
                itm.Tag = func;
                itm.SubItems.Add(func.Addr.ToString("X8"));
                itm.SubItems.Add(func.Ordinal.ToString("X"));
                listView1.Items.Add(itm);
            }
            if (func.type == 3)//Import
            {
                ListViewItem itm = new ListViewItem();
                itm.Text = func.Addr.ToString("X8");
                itm.Tag = func;
                itm.SubItems.Add(func.Ordinal.ToString("X"));
                itm.SubItems.Add(func.FName);
                itm.SubItems.Add(func.LibraryName);
                listView2.Items.Add(itm);
            }
        }
        public void OnLogEvent1(object sender, string LogStr)
        {
            Log.Items.Add(LogStr);
            //Log.SelectedIndex = Log.Items.Count-1;
        }
        private void AppendText(string text)
        {
            //some stuffs for best performance
            fastColoredTextBox1.BeginUpdate();
            fastColoredTextBox1.Selection.BeginUpdate();
            //remember user selection
            var userSelection = fastColoredTextBox1.Selection.Clone();
            //add text with predefined style
            fastColoredTextBox1.AppendText(text);
            //restore user selection
            if (!userSelection.IsEmpty || userSelection.Start.iLine < fastColoredTextBox1.LinesCount - 2)
            {
                fastColoredTextBox1.Selection.Start = userSelection.Start;
                fastColoredTextBox1.Selection.End = userSelection.End;
            }
            else
                fastColoredTextBox1.GoEnd();//scroll to end of the text
            //
            fastColoredTextBox1.Selection.EndUpdate();
            fastColoredTextBox1.EndUpdate();
        }
        delegate void SetTextCallback(string text);
        private void AddText(string text)
        {
            if (this.fastColoredTextBox1.InvokeRequired)
            {
                try
                {
                    SetTextCallback d = new SetTextCallback(AddText);
                    this.Invoke(d, new object[] { text });
                }
                catch (System.ObjectDisposedException) { }
            }
            else
            {
                AppendText(text);
            }
        }
        private void openFileDialog1_FileOk_1(object sender, CancelEventArgs e)
        {
            MyGNIDA = new GNIDA();
            MyGNIDA.OnLogEvent += OnLogEvent1;
            MyGNIDA.OnAddFunc += AddFuncEvent1;
            MyGNIDA.OnAddStr += AddText;
            MyGNIDA.OnVarEvent += AddVarEvent1;

            MyGNIDA.LoadFile(openFileDialog1.FileName);

            dynamicFileByteProvider = new DynamicFileByteProvider(openFileDialog1.FileName, true);
            hexBox1.ByteProvider = dynamicFileByteProvider;
            
            fastColoredTextBox1.Text = "//+---------------------------------------------------------------------+" +
                              "\n//| Dis file has bin generated by GNU Interactive Dissassembler (GNIDA) |" +
                              "\n//|       Copyleft (c) 2014 by me <na_derevnu@dedushke.ru>              |" +
                              "\n//|                          Free 4 use                                 |" +
                              "\n//|                         Writed AS IS                                |" +
                              "\n//+---------------------------------------------------------------------+\n"+
                              "#pragma option W32\n"+
                              "#include \"Windows.h--\";\n";
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 AboutForm = new AboutBox1();
            AboutForm.ShowDialog();
            AboutForm.Dispose();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        private void toolStripButton4_Click(object sender, EventArgs e)
        {
            MyGNIDA.StopWork();
        }

        private void cmmListingToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (fastColoredTextBox1.Text.Length > 1)
            {
                fastColoredTextBox1.SaveToFile("..\\..\\cmm\\tmp.cmm", Encoding.ASCII);

                System.Diagnostics.Process proc = new System.Diagnostics.Process();
                proc.StartInfo.FileName = "..\\..\\cmm\\c--.exe";
                proc.StartInfo.Arguments = "..\\..\\cmm\\tmp.cmm";
                proc.StartInfo.UseShellExecute = false;
                proc.StartInfo.RedirectStandardOutput = true;
                proc.Start();
                do
                {
                    Log.Items.Add(proc.StandardOutput.ReadLine());
                } while (!proc.StandardOutput.EndOfStream);
                proc.WaitForExit();
            }
        }
        private void Funclist_DoubleClick(object sender, EventArgs e)
        {
            string sss = "";
            TFunc Func = (TFunc)listView3.SelectedItems[0].Tag;
            Console.WriteLine(Func.Addr.ToString("X8"));
        }


        private void fastColoredTextBox1_ToolTipNeeded(object sender, FastColoredTextBoxNS.ToolTipNeededEventArgs e)
        {
            if (!string.IsNullOrEmpty(e.HoveredWord))
            {
                e.ToolTipTitle = e.HoveredWord;
                e.ToolTipText = "This is tooltip for '" + e.HoveredWord + "'";
            }
        }

        private void fastColoredTextBox1_TextChangedDelayed(object sender, TextChangedEventArgs e)
        {
            e.ChangedRange.ClearStyle(blueStyle);
            //e.ChangedRange.SetStyle(blueStyle, @"(http|ftp|https):\/\/[\w\-_]+(\.[\w\-_]+)+([\w\-\.,@?^=%&amp;:/~\+#]*[\w\-\@?^=%&amp;/~\+#])?");
            e.ChangedRange.SetStyle(blueStyle, @"Loc_[\dA-Fa-f]+");
        }
    }

}
