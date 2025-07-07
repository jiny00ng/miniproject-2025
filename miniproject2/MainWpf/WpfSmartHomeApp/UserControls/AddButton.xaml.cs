using System.Windows;
using System.Windows.Controls;

namespace WpfSmartHomeApp.UserControls
{
    public partial class AddButton : UserControl
    {
        public AddButton()
        {
            InitializeComponent();
        }

        public string Title
        {
            get => (string)GetValue(TitleProperty);
            set => SetValue(TitleProperty, value);
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register(
                nameof(Title),
                typeof(string),
                typeof(AddButton),
                new PropertyMetadata(string.Empty));

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            // 버튼 클릭 시 동작을 여기에 정의하거나,
            // 상위에서 이벤트를 연결할 수 있게 RoutedEvent로 구현할 수 있습니다.
        }
    }
}
