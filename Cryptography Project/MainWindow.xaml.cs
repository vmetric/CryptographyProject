using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Cryptography_Project
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Translate_Click(object sender, RoutedEventArgs e)
        {
            Encoder encoder = new Encoder();

            byte[] bytes = Encoding.UTF32.GetBytes("a");

            int result = BitConverter.ToInt32(bytes, 0);
            MessageBox.Show("Result: " + result.ToString());

            if (encoder.IsEncrypted(TBInput.Text))
            {
                TBOutput.Text = encoder.Decrypt(TBInput.Text);
            } else
            {
                TBOutput.Text = encoder.Encrypt(TBInput.Text);
            }
        }
    }
}
