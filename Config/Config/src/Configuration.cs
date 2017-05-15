using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows;
using Newtonsoft.Json;

namespace Config
{
    internal class Configuration
    {
        public enum LightShadowLevel
        {
            NONE,
            NORMAL,
            HIGH
        };

        public enum DrawInterval
        {
            ONE,
            HALF,
            ONE_THIRD
        };

        public enum StartupType
        {
            FULL_SCREEN_640_480,
            WINDOW_640_480
        }

        //render config
        public bool useMultiSample = true;

        public bool useVerticalAsync = true;
        public LightShadowLevel lightShadowLevel = LightShadowLevel.HIGH;
        public DrawInterval drawInterval = DrawInterval.ONE;

        //startup config
        public StartupType startupType = StartupType.WINDOW_640_480;

        public bool askEveryTime = true;

        public Configuration()
        {
        }

        public void SaveToFile()
        {
            string fileName = "config.json";
            string json = JsonConvert.SerializeObject(this);

            StreamWriter writer = new StreamWriter(fileName);
            writer.Write(json);
            writer.Close();
        }

        public static Configuration Create()
        {
            string fileName = "config.json";

            try
            {
                StreamReader reader = new StreamReader(fileName);
                string json = reader.ReadToEnd();
                reader.Close();
                return JsonConvert.DeserializeObject<Configuration>(json);
            }
            catch (FileNotFoundException)
            {
                return new Configuration();
            }
            catch (JsonException)
            {
                MessageBox.Show("警告：文件config.json中的配置不正确，可能导致游戏无法正常运行。请使用本程序进行配置。", "警告");
                return new Configuration();
            }
        }

        public void SetToDefault()
        {
            //render config
            useMultiSample = true;
            useVerticalAsync = true;
            lightShadowLevel = LightShadowLevel.HIGH;
            drawInterval = DrawInterval.ONE;

            //startup config
            startupType = StartupType.WINDOW_640_480;
            askEveryTime = true;
        }
    }
}