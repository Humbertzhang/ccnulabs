using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Threading;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板


namespace App4
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        const string bstr = "button";
        const string cstr = "clicked";
        const int Cnum = 8;
        const int Rnum = 8;
        static ColumnDefinition[] cdefs = new ColumnDefinition[Cnum];
        static RowDefinition[] rdefs = new RowDefinition[Rnum];
        static Button[,]buttons = new Button[Cnum, Rnum];

        public MainPage()
        {
            this.InitializeComponent();
            Loaded += MainPage_Loaded;
        }

        private void MainPage_Loaded(object sender, RoutedEventArgs e)
        {
            Grid grid = new Grid();
            grid.Width = 400;
            grid.Height = 400;
            grid.Margin = new Thickness(5, 5, 5, 5);
            for(int i = 0; i < Cnum; i+=1)
            {
                cdefs[i] = new ColumnDefinition();
                cdefs[i].Width = new GridLength(0, GridUnitType.Auto);
                grid.ColumnDefinitions.Add(cdefs[i]);
            }
            for(int i = 0; i < Rnum; i += 1)
            {
                rdefs[i] = new RowDefinition();
                rdefs[i].Height = new GridLength(0, GridUnitType.Auto);
                grid.RowDefinitions.Add(rdefs[i]);
            }


            for(int i = 0; i < Cnum; i+= 1)
            {
                for(int j = 0; j < Rnum; j+=1)
                {
                    Button button = new Button();
                    button.Content = bstr;
                    //button.Width = 100;
                    //button.Height = 100;
                    button.Margin = new Thickness(1, 1, 1, 1);
                    button.HorizontalAlignment = HorizontalAlignment.Stretch;
                    button.VerticalAlignment = VerticalAlignment.Stretch;
                    button.Background = new SolidColorBrush(Windows.UI.Colors.Gray);
                    Grid.SetRow(button, i);
                    Grid.SetColumn(button, j);
                    grid.Children.Add(button);
                    button.Click += Button_Click;
                    buttons[i, j] = button;
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Button b = (Button)sender;
            
            if (b.Content == bstr)
            {
                b.Content = cstr;
                b.Background = new SolidColorBrush(Windows.UI.Colors.Orange);
            }
            else
            {
                b.Content = bstr;
                b.Background = new SolidColorBrush(Windows.UI.Colors.Gray);
            }
            
        }
    }
}
