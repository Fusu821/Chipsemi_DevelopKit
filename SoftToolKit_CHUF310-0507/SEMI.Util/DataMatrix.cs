using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace SEMI.Util
{
    public class MatrixColumn
    {
        public string Name { get; set; }
        public string FormatString { get; set; }

        public MatrixColumn(string name)
        {
            Name = name;
        }
        public override string ToString()
        {
            return this.Name;
        }
    }
    public class MatrixRow : INotifyPropertyChanged
    {
        public object Col00 { get { return items.Length >= 1 ? items[0] : null; } set { items[0] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 0, items[0], value); } }
        public object Col01 { get { return items.Length >= 2 ? items[1] : null; } set { items[1] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 1, items[1], value); } }
        public object Col02 { get { return items.Length >= 3 ? items[2] : null; } set { items[2] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 2, items[2], value); } }
        public object Col03 { get { return items.Length >= 4 ? items[3] : null; } set { items[3] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 3, items[3], value); } }
        public object Col04 { get { return items.Length >= 5 ? items[4] : null; } set { items[4] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 4, items[4], value); } }
        public object Col05 { get { return items.Length >= 6 ? items[5] : null; } set { items[5] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 5, items[5], value); } }
        public object Col06 { get { return items.Length >= 7 ? items[6] : null; } set { items[6] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 6, items[6], value); } }
        public object Col07 { get { return items.Length >= 8 ? items[7] : null; } set { items[7] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 7, items[7], value); } }
        public object Col08 { get { return items.Length >= 9 ? items[8] : null; } set { items[8] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 8, items[8], value); } }
        public object Col09 { get { return items.Length >= 10 ? items[9] : null; } set { items[9] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 9, items[9], value); } }
        public object Col10 { get { return items.Length >= 11 ? items[10] : null; } set { items[10] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 10, items[10], value); } }
        public object Col11 { get { return items.Length >= 12 ? items[11] : null; } set { items[11] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 11, items[11], value); } }
        public object Col12 { get { return items.Length >= 13 ? items[12] : null; } set { items[12] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 12, items[12], value); } }
        public object Col13 { get { return items.Length >= 14 ? items[13] : null; } set { items[13] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 13, items[13], value); } }
        public object Col14 { get { return items.Length >= 15 ? items[14] : null; } set { items[14] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 14, items[14], value); } }
        public object Col15 { get { return items.Length >= 16 ? items[15] : null; } set { items[15] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 15, items[15], value); } }
        public object Col16 { get { return items.Length >= 17 ? items[16] : null; } set { items[16] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 16, items[16], value); } }
        public object Col17 { get { return items.Length >= 18 ? items[17] : null; } set { items[17] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 17, items[17], value); } }
        public object Col18 { get { return items.Length >= 19 ? items[18] : null; } set { items[18] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 18, items[18], value); } }
        public object Col19 { get { return items.Length >= 20 ? items[19] : null; } set { items[19] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 19, items[19], value); } }
        public object Col20 { get { return items.Length >= 21 ? items[20] : null; } set { items[20] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 20, items[20], value); } }
        public object Col21 { get { return items.Length >= 22 ? items[21] : null; } set { items[21] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 21, items[21], value); } }
        public object Col22 { get { return items.Length >= 23 ? items[22] : null; } set { items[22] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 22, items[22], value); } }
        public object Col23 { get { return items.Length >= 24 ? items[23] : null; } set { items[23] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 23, items[23], value); } }
        public object Col24 { get { return items.Length >= 25 ? items[24] : null; } set { items[24] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 24, items[24], value); } }
        public object Col25 { get { return items.Length >= 26 ? items[25] : null; } set { items[25] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 25, items[25], value); } }
        public object Col26 { get { return items.Length >= 27 ? items[26] : null; } set { items[26] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 26, items[26], value); } }
        public object Col27 { get { return items.Length >= 28 ? items[27] : null; } set { items[27] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 27, items[27], value); } }
        public object Col28 { get { return items.Length >= 29 ? items[28] : null; } set { items[28] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 28, items[28], value); } }
        public object Col29 { get { return items.Length >= 30 ? items[29] : null; } set { items[29] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 29, items[29], value); } }
        public object Col30 { get { return items.Length >= 31 ? items[30] : null; } set { items[30] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 30, items[30], value); } }
        public object Col31 { get { return items.Length >= 32 ? items[31] : null; } set { items[31] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 31, items[31], value); } }
        public object Col32 { get { return items.Length >= 33 ? items[32] : null; } set { items[32] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 32, items[32], value); } }
        public object Col33 { get { return items.Length >= 34 ? items[33] : null; } set { items[33] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 33, items[33], value); } }
        public object Col34 { get { return items.Length >= 35 ? items[34] : null; } set { items[34] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 34, items[34], value); } }
        public object Col35 { get { return items.Length >= 36 ? items[35] : null; } set { items[35] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 35, items[35], value); } }
        public object Col36 { get { return items.Length >= 37 ? items[36] : null; } set { items[36] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 36, items[36], value); } }
        public object Col37 { get { return items.Length >= 38 ? items[37] : null; } set { items[37] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 37, items[37], value); } }
        public object Col38 { get { return items.Length >= 39 ? items[38] : null; } set { items[38] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 38, items[38], value); } }
        public object Col39 { get { return items.Length >= 40 ? items[39] : null; } set { items[39] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 39, items[39], value); } }
        public object Col40 { get { return items.Length >= 41 ? items[40] : null; } set { items[40] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 40, items[40], value); } }
        public object Col41 { get { return items.Length >= 42 ? items[41] : null; } set { items[41] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 41, items[41], value); } }
        public object Col42 { get { return items.Length >= 43 ? items[42] : null; } set { items[42] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 42, items[42], value); } }
        public object Col43 { get { return items.Length >= 44 ? items[43] : null; } set { items[43] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 43, items[43], value); } }
        public object Col44 { get { return items.Length >= 45 ? items[44] : null; } set { items[44] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 44, items[44], value); } }
        public object Col45 { get { return items.Length >= 46 ? items[45] : null; } set { items[45] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 45, items[45], value); } }
        public object Col46 { get { return items.Length >= 47 ? items[46] : null; } set { items[46] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 46, items[46], value); } }
        public object Col47 { get { return items.Length >= 48 ? items[47] : null; } set { items[47] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 47, items[47], value); } }
        public object Col48 { get { return items.Length >= 49 ? items[48] : null; } set { items[48] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 48, items[48], value); } }
        public object Col49 { get { return items.Length >= 50 ? items[49] : null; } set { items[49] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 49, items[49], value); } }
        public object Col50 { get { return items.Length >= 51 ? items[50] : null; } set { items[50] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 50, items[50], value); } }
        public object Col51 { get { return items.Length >= 52 ? items[51] : null; } set { items[51] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 51, items[51], value); } }
        public object Col52 { get { return items.Length >= 53 ? items[52] : null; } set { items[52] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 52, items[52], value); } }       
        public object Col53 { get { return items.Length >= 54 ? items[53] : null; } set { items[53] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 53, items[53], value); } }
        public object Col54 { get { return items.Length >= 55 ? items[54] : null; } set { items[54] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 54, items[54], value); } }
        public object Col55 { get { return items.Length >= 56 ? items[55] : null; } set { items[55] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 55, items[55], value); } }
        public object Col56 { get { return items.Length >= 57 ? items[56] : null; } set { items[56] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 56, items[56], value); } }
        public object Col57 { get { return items.Length >= 58 ? items[57] : null; } set { items[57] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 57, items[57], value); } }
        public object Col58 { get { return items.Length >= 59 ? items[58] : null; } set { items[58] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 58, items[58], value); } }
        public object Col59 { get { return items.Length >= 60 ? items[59] : null; } set { items[59] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 59, items[59], value); } }
        public object Col60 { get { return items.Length >= 61 ? items[60] : null; } set { items[60] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 60, items[60], value); } }
        public object Col61 { get { return items.Length >= 62 ? items[61] : null; } set { items[61] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 61, items[61], value); } }
        public object Col62 { get { return items.Length >= 63 ? items[62] : null; } set { items[62] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 62, items[62], value); } }
        public object Col63 { get { return items.Length >= 64 ? items[63] : null; } set { items[63] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 63, items[63], value); } }
        public object Col64 { get { return items.Length >= 65 ? items[64] : null; } set { items[64] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 64, items[64], value); } }
        public object Col65 { get { return items.Length >= 66 ? items[65] : null; } set { items[65] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 65, items[65], value); } }
        public object Col66 { get { return items.Length >= 67 ? items[66] : null; } set { items[66] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 66, items[66], value); } }
        public object Col67 { get { return items.Length >= 68 ? items[67] : null; } set { items[67] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 67, items[67], value); } }
        public object Col68 { get { return items.Length >= 69 ? items[68] : null; } set { items[68] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 68, items[68], value); } }
        public object Col69 { get { return items.Length >= 70 ? items[69] : null; } set { items[69] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 69, items[69], value); } }
        public object Col70 { get { return items.Length >= 71 ? items[70] : null; } set { items[70] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 70, items[70], value); } }
        public object Col71 { get { return items.Length >= 72 ? items[71] : null; } set { items[71] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 71, items[71], value); } }
        public object Col72 { get { return items.Length >= 73 ? items[72] : null; } set { items[72] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 72, items[72], value); } }
        public object Col73 { get { return items.Length >= 74 ? items[73] : null; } set { items[73] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 73, items[73], value); } }
        public object Col74 { get { return items.Length >= 75 ? items[74] : null; } set { items[74] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 74, items[74], value); } }
//         public object Col76 { get { return items.Length >= 76 ? items[75] : null; } set { items[75] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 75, items[75], value); } }
//         public object Col77 { get { return items.Length >= 77 ? items[76] : null; } set { items[76] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 76, items[76], value); } }
//         public object Col78 { get { return items.Length >= 78 ? items[77] : null; } set { items[77] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 77, items[77], value); } }
//         public object Col79 { get { return items.Length >= 79 ? items[78] : null; } set { items[78] = int.Parse(value.ToString()); parentParam.NotifyValueChanged(RowIndex, 78, items[78], value); } }
        public object[] items { get; set; }
        public MatrixRow(int curIndex, object[] itemsTemp)
        {
            items = itemsTemp;
            RowIndex = curIndex;
        }

        public event PropertyChangedEventHandler PropertyChanged;
        public virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;

            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public int RowIndex { get; private set; }

        public MatrixParam parentParam { get; set; }
        

        public object this[int index]
        {
            get { return items[index]; }
            set
            {
                if (value != items[index])
                {
                    items[index] = value;
                    OnPropertyChanged("Col" + (index /*+ 1*/).ToString("00"));
                }
            }
        }
    }
     public class MatrixParam
     {
//         public DataMatrix.ValueChangedCallBack OnMatrixValueChangedCopy { private get; set; }
//         public delegate void ValueChangedCallBack(int row, int col, object oldVal, object newVal);
//         public int Col { get; private set; }
//         public object[] RowObject { get; set; }
         public DataMatrix Parent { get; private set; }
         public MatrixParam(DataMatrix matrix)
         {
             //Col = col;
             Parent = matrix;
         }
         public void NotifyValueChanged(int row, int col, object oldVal, object newVal)
         {
             if (null != Parent.OnMatrixValueChanged)
                 Parent.OnMatrixValueChanged(row, col, oldVal, newVal);
         }
     }
    public class DataMatrix
    {
        public List<MatrixColumn> Columns { get; private set; }
        public ObservableCollection<MatrixRow> Rows { get; private set; }
        //public int RowExts { get; set; }
        public ValueChangedCallBack OnMatrixValueChanged { get;  set; }

        public delegate void ValueChangedCallBack(int row, int col, object oldVal, object newVal);
        public DataMatrix(int rows, int cols, int rowexp = 0, int colexp = 0, ValueChangedCallBack callBack = null)
        {
            //Keys = keys;
            RowExp = rowexp;
            ColExp = colexp;
            OnMatrixValueChanged = callBack;
            Columns = new List<MatrixColumn>(new MatrixColumn[cols + (colexp > 0 ? 1 : 0)]);
            Rows = new ObservableCollection<MatrixRow>(new MatrixRow[rows + (rowexp > 0 ? 1 : 0)]);

            if (null == OnMatrixValueChanged)
            {
                OnMatrixValueChanged = new ValueChangedCallBack((row, col, oldVal, newVal) =>
                {
                    Rows[row].OnPropertyChanged("Col" + (col /*+ 1*/).ToString("00"));
                });
            }

            for (int index = 0; index < Columns.Count; index++)
            {
                Columns[index] = new MatrixColumn(string.Format("Col{0:D2}", index /*+ 1*/));
            }
            for (int index = 0; index < Rows.Count; index++)
            {
                object[] objArray = new object[Columns.Count];
                Rows[index] = new MatrixRow(index, objArray);
                Rows[index].parentParam = new MatrixParam(this);
            }
        }
        /// <summary>
        /// （this声明索引器，可以通过索引器访问实例成员——ZR注）
        /// </summary>
        /// <param name="index"></param>
        /// <returns></returns>
        public MatrixRow this[int index]
        {
            get
            {
                return Rows[index];
            }
            set
            {
                Rows[index] = value;
            }
        }
        public int RowNumber { get { return Rows.Count; } }
        public int ColNumber { get { return Columns.Count; } }
        public int RowExp { get; set; }
        public int ColExp { get; set; }
    }
}
