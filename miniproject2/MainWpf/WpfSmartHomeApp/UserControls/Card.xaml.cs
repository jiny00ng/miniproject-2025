using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace WpfSmartHomeApp.UserControls
{
    public partial class Card : UserControl
    {
        public Card()
        {
            InitializeComponent();
        }

        public string Title
        {
            get => (string)GetValue(TitleProperty);
            set => SetValue(TitleProperty, value);
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register(nameof(Title), typeof(string), typeof(Card), new PropertyMetadata(string.Empty));

        public bool IsChecked
        {
            get => (bool)GetValue(IsCheckedProperty);
            set => SetValue(IsCheckedProperty, value);
        }

        public static readonly DependencyProperty IsCheckedProperty =
            DependencyProperty.Register(nameof(IsChecked), typeof(bool), typeof(Card),
                new PropertyMetadata(false, OnCheckedChanged));

        public string ImageOn
        {
            get => (string)GetValue(ImageOnProperty);
            set => SetValue(ImageOnProperty, value);
        }

        public static readonly DependencyProperty ImageOnProperty =
            DependencyProperty.Register(nameof(ImageOn), typeof(string), typeof(Card), new PropertyMetadata(string.Empty));

        public string ImageOff
        {
            get => (string)GetValue(ImageOffProperty);
            set => SetValue(ImageOffProperty, value);
        }

        public static readonly DependencyProperty ImageOffProperty =
            DependencyProperty.Register(nameof(ImageOff), typeof(string), typeof(Card), new PropertyMetadata(string.Empty));

        public BitmapImage CurrentImageSource => new BitmapImage(new Uri(IsChecked ? ImageOn : ImageOff, UriKind.RelativeOrAbsolute));

        private static void OnCheckedChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is Card c)
            {
                // Force UI refresh
                c.OnPropertyChanged(nameof(CurrentImageSource));
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            IsChecked = !IsChecked;
        }

        protected void OnPropertyChanged(string name)
        {
            var prop = GetType().GetProperty(name);
        }
    }
}
