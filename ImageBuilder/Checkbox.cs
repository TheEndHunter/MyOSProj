namespace ImageBuilder
{
    using System;
    using System.Collections.Generic;

    public class Checkbox
    {
        private readonly List<CheckboxOptions> _options;
        private int _hoveredIndex;
        private int _selectedIndex;
        private readonly string _displayText;
        private readonly bool _multiSelect;
        private readonly bool _required;
        private bool _error;
        private ConsoleKey _key;
        private ConsoleKey _prevKey;

        private readonly ConsoleColor _SelectedColor = ConsoleColor.Blue;
        private readonly ConsoleColor _SelectedHoveredColor = ConsoleColor.White;
        private readonly ConsoleColor _UnselectedHoveredColor = ConsoleColor.DarkBlue;
        private readonly ConsoleColor _UnselectedColor = ConsoleColor.DarkGray;

        public Checkbox(string displayText, IEnumerable<string> options, IEnumerable<string>? selected = null, ConsoleColor unselectedColor = ConsoleColor.DarkCyan, ConsoleColor unselectedHoveredColor = ConsoleColor.Cyan, ConsoleColor selectedColor = ConsoleColor.DarkGreen, ConsoleColor selectedHoveredColor = ConsoleColor.Green, bool multiSelect = false, bool required = true)
        {
            _multiSelect = multiSelect;
            _required = required;
            _SelectedColor = selectedColor;
            _SelectedHoveredColor = selectedHoveredColor;
            _UnselectedHoveredColor = unselectedHoveredColor;
            _UnselectedColor = unselectedColor;
            _hoveredIndex = 0;
            _selectedIndex = -1;
            _error = false;
            _displayText = displayText;

            _options = [];

            int i = 0;

            if (multiSelect && selected != null && selected.Any())
            {
                foreach (var option in options.OrderBy(x => x))
                {
                    if (selected.Contains(option,StringComparer.CurrentCultureIgnoreCase))
                        _options.Add(new CheckboxOptions(option, true, false, i));
                    else
                        _options.Add(new CheckboxOptions(option, false, false, i));
                    i++;
                }
            }
            else
            {
                foreach (var option in options)
                {
                    _options.Add(new CheckboxOptions(option, false, false, i));
                    i++;
                }
            }


            
        }

        private IEnumerable<CheckboxReturn> ReturnData()
        {
            return _options.Where(x => x.Selected).Select(x => x.GetData());
        }

        public void Show()
        {
            Console.Clear();
            Console.WriteLine(_displayText);

            if (_multiSelect)
            {
                Console.WriteLine("(Use Arrow keys to navigate up and down, Space bar to select items and Enter to submit)");
            }
            else
            {
                Console.WriteLine("(Use Arrow keys to navigate up and down, Space bar to select an item)");
            }

            foreach (var option in _options)
            {
                Console.ForegroundColor = option.Selected ? (option.Hovered ? _SelectedHoveredColor : _SelectedColor) : (option.Hovered ? _UnselectedHoveredColor : _UnselectedColor);

                Console.WriteLine((option.Selected ? "[*]: " : "[ ]: ") + $"{option.Option}");
            }
            Console.ResetColor();
            if (_error) Console.WriteLine($"{Environment.NewLine}At least one item has to be selected!");
        }

        public IEnumerable<CheckboxReturn> Select()
        {
            Show();
            bool end = false;
            while (!end)
            {
                _key = Console.KeyAvailable ? Console.ReadKey(true).Key : ConsoleKey.D9;
                if (_key == _prevKey) continue;

                _options[_hoveredIndex].Hovered = false;

                switch (_key)
                {
                    case ConsoleKey.UpArrow:
                    case ConsoleKey.W:
                        _hoveredIndex = _hoveredIndex - 1 >= 0 ? _hoveredIndex - 1 : _options.Count - 1;
                        break;

                    case ConsoleKey.DownArrow:
                    case ConsoleKey.S:
                        _hoveredIndex = _hoveredIndex + 1 < _options.Count ? _hoveredIndex + 1 : 0;
                        break;

                    case ConsoleKey.Spacebar:
                        _options[_hoveredIndex].Selected = !_options[_hoveredIndex].Selected;
                        if (!_multiSelect)
                        {
                            if (_selectedIndex > -1 && _hoveredIndex != _selectedIndex)
                                _options[_selectedIndex].Selected = false;

                            _selectedIndex = _hoveredIndex;

                            if (_required)
                            {
                                foreach (var option in _options)
                                {
                                    if (!option.Selected) continue;
                                    end = true;
                                    break;
                                }

                                if (!end) _error = true;
                            }
                            else end = true;
                            break;
                        }

                        _error = false;
                        break;

                    case ConsoleKey.Enter:
                        if (_required)
                        {
                            foreach (var option in _options)
                            {
                                if (!option.Selected) continue;
                                end = true;
                                break;
                            }

                            if (!end) _error = true;
                        }
                        else end = true;

                        break;
                }

                _options[_hoveredIndex].Hovered = true;
                Show();
                _prevKey = _key;
            }

            return ReturnData();
        }
    }

    public class CheckboxOptions(string Option, bool Selected, bool Hovered, int Index)
    {
        public readonly string Option = Option;
        public bool Selected = Selected;
        public bool Hovered = Hovered;
        public readonly int Index = Index;
        public CheckboxReturn GetData()
        {
            return new CheckboxReturn(Index, Option);
        }
    }

    public readonly record struct CheckboxReturn
    {
        public CheckboxReturn(int index, string option)
        {
            Index = index;
            Option = option;
        }

        public readonly int Index;
        public readonly string Option;

    }
}
