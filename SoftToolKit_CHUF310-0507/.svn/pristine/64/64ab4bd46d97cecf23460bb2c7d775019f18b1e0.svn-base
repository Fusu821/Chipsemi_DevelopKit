using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

using sz_value_pair = System.Collections.Generic.KeyValuePair<SRange, int>;
using matrix_list = System.Collections.Generic.List<int[,]>;

namespace SEMI.Util
{
    public class FileParse
    {
        public string szFileName { get; private set; }
        public string szContent { get; private set; }
        private IDictionary<string, int[,]> dcContent = new Dictionary<string, int[,]>();
        public IDictionary<string, int[,]> ContentMap
        {
            get { return dcContent; }
            private set { }
        }

        public FileParse(string fileName, string content)
        {
            szFileName = fileName;
            szContent = content;
        }
    }
    public class Statistic
    {
        private IList<FileParse> lsFileParse = new List<FileParse>();
        private IDictionary<string, matrix_list> dcStatisticCollection = new Dictionary<string, matrix_list>();


        public int TotalCount()
        {
            return lsFileParse.Count();
        }
        public IList<sz_value_pair> GetStatisticResult(string keyWord, int Rows, int Cols, int px, int py, int minVal = 0, int maxVal = 0)
        {
            List <sz_value_pair> lsVals = new List<sz_value_pair>();

            if(!dcStatisticCollection.ContainsKey(keyWord))
                dcStatisticCollection[keyWord] = GetListOfData(keyWord, Rows, Cols, new int[]{Cols});

            IList<int> ls_of_points = GetListDataPoint(dcStatisticCollection[keyWord], px, py);
            if (ls_of_points.Count == 0) return lsVals;

            int hist_pairs_num = Math.Min(200, ls_of_points.Count());
            hist_pairs_num = Math.Max(hist_pairs_num, 50);
            double step = ((double)(maxVal - minVal)) / hist_pairs_num;
            for (double dwIter = minVal; dwIter <= maxVal; dwIter+= step)
            {
                SRange range = new SRange(dwIter, step);
                int counter = ls_of_points.Count(t => t > range.Left && t <= range.Right ? true : false);
                sz_value_pair cur = new sz_value_pair(range, counter);
                lsVals.Add(cur);
            }

            return lsVals;
        }

        public void PrepareStatistic(string folder, Boolean excludeTBD)
        {
            DirectoryInfo rootInfo = new DirectoryInfo(folder);
            Stack<DirectoryInfo> queueDir = new Stack<DirectoryInfo>();

            dcStatisticCollection.Clear();
            lsFileParse.Clear();

            var action = new Action<FileInfo[]>((fileList) =>
            {
                foreach (FileInfo NextFile in fileList)
                {
                    if (!NextFile.Name.Contains(".txt")) continue;

                    int lengh = (int)NextFile.Length;
                    char[] fileContent = new char[lengh];
                    StreamReader sr = new StreamReader(NextFile.FullName, Encoding.Default);
                    sr.Read(fileContent, 0, lengh);
                    sr.Close();

                    string content = new string(fileContent);
                    lsFileParse.Add(new FileParse(NextFile.FullName, content.Replace("\r\n", "\n")));
                }
            });

            queueDir.Push(rootInfo);
            while (queueDir.Count > 0)
            {
                DirectoryInfo dirInfo = queueDir.Pop();
                if (excludeTBD && dirInfo.Name == "TBDLog")
                {

                }
                else
                {
                    action(dirInfo.GetFiles());
                }
                

                foreach (var item in dirInfo.GetDirectories())
                    queueDir.Push(item);
            }
        }

        public List<int[,]> GetListOfData(string szKeyword, int Rows, int maxCols, int[] pCols = null, List<FileParse> retFiles = null)
        {
            List<int[,]> ls_of_data = new List<int[,]>();

            foreach(var parser in lsFileParse)
            {
                if (parser.ContentMap.ContainsKey(szKeyword))
                {
                    ls_of_data.Add(parser.ContentMap[szKeyword]);
                    continue;
                }

                var item = parser.szContent;
                int iStump = item.LastIndexOf(szKeyword);
                if (iStump < 0) continue;

                int pointStump = item.IndexOf("Point", iStump);
                if (pointStump - iStump > 0 && pointStump - iStump < (10 + szKeyword.Length))
                {
                    iStump = item.LastIndexOf(szKeyword, iStump - 1);
                }
                if (iStump < 0) continue;

                int iStart = item.IndexOf("\n", iStump) + ("\n").Length;
                int iEnded = item.IndexOf("\n\n", iStart);
                int iEnded1 = item.IndexOf("\r\n\r\n", iStart);
                if (iEnded > 0 && iEnded1>0)
                {
                    iEnded = iEnded > iEnded1 ? iEnded1 : iEnded;
                }
                else
                {
                    iEnded = iEnded > iEnded1 ? iEnded : iEnded1;
                }
                if (iEnded < 0) continue;
                if (iStart >= iEnded) continue;

                int[,] data = new int[Rows + 1, maxCols];

                string szData = item.Substring(iStart, iEnded - iStart);
                szData = szData.Replace(",", " ");
                szData = szData.Replace("\n", " ");
                szData = szData.Replace("\r", " ");
                szData = szData.Replace("\t", " ");
                szData = szData.Replace("/", "0");
                var dataSplite = szData.Split(' ').Where(t => t.Length > 0 && !t.Contains("Row") && !t.Contains("Col") && !t.Contains("Tx") && !t.Contains("Rx")).ToList();

                int iRow = 0, iCol = 0;
                for (int iParsePos = 0; iParsePos < dataSplite.Count(); iParsePos++)
                {
                    //data[Rows, iCol] = int.Parse(dataSplite.ElementAt(Rows * Cols + iCol).Trim());
                    if (iRow >= data.GetLength(0)) break;
                    if (iCol >= data.GetLength(1)) continue;

                    data[iRow, iCol] = int.Parse(dataSplite.ElementAt(iParsePos).Trim());

                    int cultOff = (null == pCols) ? maxCols : pCols[iRow >= pCols.Length ? pCols.Length - 1 : iRow];

                    if (++iCol >= cultOff)
                    {
                        iRow++;
                        iCol = 0;
                    }
                }

               ls_of_data.Add(data);
               if (null != retFiles) retFiles.Add(parser);
               parser.ContentMap[szKeyword] = data;  
            }

            return ls_of_data;
        }

        IList<int> GetListDataPoint(IList<int[,]> list_of_data, int px, int py)
        {
            return list_of_data.Select(t => t[px, py]).ToList();
        }

        public void TickOut(string KeyWords, ref IList<FileParse> lsContent, int Rows, int Cols, int tickRatio, int offset_t = 0)
        {
            double[,] retSample = new double[Rows, Cols];
            
            List<int[,]> ls_of_data = GetListOfData(KeyWords, Rows, Cols);
            if (0 == ls_of_data.Count) return;

            lsContent = lsFileParse;

            for(int iRow = 0; iRow < Rows; iRow++)
                for(int iCol = 0; iCol < Cols; iCol++)
                    retSample[iRow, iCol] = ls_of_data.Average(o => o[iRow, iCol]) - offset_t;

//             for (int iRow = 0; iRow < Rows; iRow++)
//                 for (int iCol = 0; iCol < Cols; iCol++)
//                     retSample[iRow, iCol] = (double)retSample[iRow, iCol] / (ls_of_data.Count() > 0 ? ls_of_data.Count() : 1) - offset_t;

            if (tickRatio > 0)
            {
                IEnumerable<FileParse> listCopy = lsContent.Where((content) =>
                {
                    if (!content.ContentMap.ContainsKey(KeyWords))
                        return false;
                    int[,] matrixs = content.ContentMap[KeyWords];

                    for (int iRow = 0; iRow < Rows; iRow++)
                    {
                        for (int iCol = 0; iCol < Cols; iCol++)
                        {
                            double curSample = matrixs[iRow, iCol] - offset_t;
                            if (Math.Abs(curSample - retSample[iRow, iCol]) > Math.Abs(retSample[iRow, iCol]) * tickRatio / 100)
                                return false;
                        }
                    }

                    return true;
                });

                lsContent = listCopy.ToList();
            }
        }

        public void TickOutMScap(string KeyWords, ref IList<FileParse> lsContent, int Cols1, int Cols2, int tickRatio, int offset_t = 0)
        {
            double[,] retSample = new double[2, Math.Max(Cols1, Cols2)];

            List<int[,]> ls_of_data = GetListOfData(KeyWords, 2, Math.Max(Cols1, Cols2), new int[] { Cols1, Cols2 });
            if (0 == ls_of_data.Count) return;

            lsContent = lsFileParse;

            for (int iCol = 0; iCol < Cols1; iCol++)
                retSample[0, iCol] = ls_of_data.Average(o => o[0, iCol]) - offset_t;
            for (int iCol = 0; iCol < Cols2; iCol++)
                retSample[1, iCol] = ls_of_data.Average(o => o[1, iCol]) - offset_t;

            if (tickRatio > 0)
            {
                IEnumerable<FileParse> listCopy = lsContent.Where((content) =>
                {
                    if (!content.ContentMap.ContainsKey(KeyWords))
                        return false;
                    int[,] matrixs = content.ContentMap[KeyWords];

                    for (int iCol = 0; iCol < Cols1; iCol++)
                    {
                        double curSample = matrixs[0, iCol] - offset_t;
                        if (Math.Abs(curSample - retSample[0, iCol]) > Math.Abs(retSample[0, iCol]) * tickRatio / 100)
                            return false;
                    }
                    for (int iCol = 0; iCol < Cols2; iCol++)
                    {
                        double curSample = matrixs[1, iCol] - offset_t;
                        if (Math.Abs(curSample - retSample[1, iCol]) > Math.Abs(retSample[1, iCol]) * tickRatio / 100)
                            return false;
                    }

                    return true;
                });

                lsContent = listCopy.ToList();
            }
        }

    }
}
