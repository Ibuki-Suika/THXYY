using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

namespace Config
{
    public partial class MainWindow : Window
    {
        private Configuration config;

        private Configuration.DrawInterval[] drawIntervals = new Configuration.DrawInterval[]
        {
            Configuration.DrawInterval.ONE_THIRD,
            Configuration.DrawInterval.HALF,
            Configuration.DrawInterval.ONE
        };

        private Configuration.LightShadowLevel[] lightLevels = new Configuration.LightShadowLevel[]
        {
            Configuration.LightShadowLevel.NONE,
            Configuration.LightShadowLevel.NORMAL,
            Configuration.LightShadowLevel.HIGH
        };

        private Configuration.StartupType[] startupTypes = new Configuration.StartupType[]
        {
            Configuration.StartupType.FULL_SCREEN_640_480,
            Configuration.StartupType.WINDOW_640_480
        };

        public void SaveConfig()
        {
            //render config
            config.useMultiSample = (bool)checkBox_useMultiSample.IsChecked;
            config.useVSync = (bool)checkBox_useVerticalAsync.IsChecked;
            config.lightShadowLevel = lightLevels[combo_lightLevel.SelectedIndex];
            config.drawInterval = drawIntervals[combo_drawInterval.SelectedIndex];

            //startup config
            config.startupType = startupTypes[combo_startupType.SelectedIndex];
            config.askEveryTime = (bool)checkBox_askEveryTime.IsChecked;

            config.SaveToFile();
        }

        private void Update()
        {
            //render config
            checkBox_useMultiSample.IsChecked = config.useMultiSample;
            checkBox_useVerticalAsync.IsChecked = config.useVSync;

            combo_drawInterval.IsEnabled = !config.useVSync;

            switch (config.lightShadowLevel)
            {
                case Configuration.LightShadowLevel.NONE:
                    combo_lightLevel.SelectedIndex = 0;
                    break;

                case Configuration.LightShadowLevel.NORMAL:
                    combo_lightLevel.SelectedIndex = 1;
                    break;

                case Configuration.LightShadowLevel.HIGH:
                    combo_lightLevel.SelectedIndex = 2;
                    break;

                default:
                    throw new ArgumentException("Unknown LightShadowLevel type");
            }
            switch (config.drawInterval)
            {
                case Configuration.DrawInterval.ONE_THIRD:
                    combo_drawInterval.SelectedIndex = 0;
                    break;

                case Configuration.DrawInterval.HALF:
                    combo_drawInterval.SelectedIndex = 1;
                    break;

                case Configuration.DrawInterval.ONE:
                    combo_drawInterval.SelectedIndex = 2;
                    break;

                default:
                    throw new ArgumentException("Unknown DrawInterval type");
            }

            //startup config
            checkBox_askEveryTime.IsChecked = config.askEveryTime;
            switch (config.startupType)
            {
                case Configuration.StartupType.FULL_SCREEN_640_480:
                    combo_startupType.SelectedIndex = 0;
                    break;

                case Configuration.StartupType.WINDOW_640_480:
                    combo_startupType.SelectedIndex = 1;
                    break;

                default:
                    throw new ArgumentException("Unknown StartupType type");
            }
        }
    }
}