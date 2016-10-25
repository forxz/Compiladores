Imports System.IO
Imports System.Text.RegularExpressions

Public Class Form1
    Dim rutaArchivo$ = ""
    Dim Numero As Integer
    Dim Claves = {"and", "array", "average", "bool", "break", "case", "char", "closeFile",
                  "compare", "concat", "cond", "do", "default", "else", "even", "factorial", "false", "file",
                  "float", "for", "function", "if", "int", "main", "null", "openFile",
                  "or", "pow", "print", "procedure", "read", "ref", "repeat", "return",
                  "sort", "string", "substring", "switch", "true", "until", "while"} 'PALABRAS CLAVE.
    Dim active_color As Boolean = True

    Private Declare Function LockWindowUpdate Lib "user32" (ByVal hWnd As Integer) As Integer 'BLOQUEA AL REPINTADO DEL TEXTO PARA EVITAR PARPADEO

    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click, AbrirDoc.Click
        Dim Abrir As New OpenFileDialog()
        Dim STR As System.IO.StreamReader
        Abrir.Filter = "Text(*.txt)|*.txt" 'Tipo de archivo a utilizar
        Abrir.CheckFileExists = True 'Comprueba que el archivo exista
        Abrir.Title = "Abrir documento"
        If Abrir.ShowDialog(Me) = Windows.Forms.DialogResult.OK Then 'Muestra ventana para seleccionar el archivo a abrir
            Try
                STR = System.IO.File.OpenText(Abrir.FileName) 'Lee el archivo
                RichTextBox1.Text = STR.ReadToEnd() 'Muestra el contenido del archivo en pantalla
                STR.Close()
                rutaArchivo = Abrir.FileName
            Catch ex As Exception
                MessageBox.Show(ex.Message, "Error al leer archivo", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End Try
        End If
    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click, NuevoDoc.Click
        RichTextBox1.Clear() 'Limpia la pantalla para redactar un nuevo documento
        rutaArchivo = ""
    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click, GuardarDoc.Click
        Dim saveFile1 As New SaveFileDialog()
        saveFile1.DefaultExt = "*.rtf"
        saveFile1.Filter = "Text Files|*.txt"
        If (saveFile1.ShowDialog() = System.Windows.Forms.DialogResult.OK) _
            And (saveFile1.FileName.Length) > 0 Then
            RichTextBox1.SaveFile(saveFile1.FileName, RichTextBoxStreamType.PlainText)
            rutaArchivo = saveFile1.FileName
            MessageBox.Show("Guardado con éxito", "Archivo Guardado", MessageBoxButtons.OK, MessageBoxIcon.Information)
        End If

    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Me.Close() 'Cierra el editor
    End Sub

    Private Sub DeshacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DeshacerToolStripMenuItem.Click, Undo.Click
        RichTextBox1.Undo() 'Deshace cambios realizados en el texto
    End Sub

    Private Sub RehacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RehacerToolStripMenuItem.Click, Redo.Click
        RichTextBox1.Redo() 'Rehace cambios realizados en el texto
    End Sub

    Private Sub CortarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CortarToolStripMenuItem.Click, CortarTexto.Click
        RichTextBox1.Cut() 'Corta texto seleccionado
    End Sub

    Private Sub CopiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarToolStripMenuItem.Click
        RichTextBox1.Copy() 'Copia texto seleccionado
    End Sub

    Private Sub PegarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PegarToolStripMenuItem.Click, PegarTexto.Click
        RichTextBox1.Paste() 'Pega texto seleccionado
    End Sub

    Private Sub SeleccionarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SeleccionarTodoToolStripMenuItem.Click
        RichTextBox1.SelectAll() 'Selecciona todo el texto del editor
    End Sub

    Private Sub LimpiarTexoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LimpiarTexoToolStripMenuItem.Click
        RichTextBox1.Clear() 'Limpia la pantalla del editor
    End Sub

    Private Sub FuenteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles Fuente.Click
        Try
            Dim fuente As FontDialog = New FontDialog
            fuente.Font = RichTextBox1.Font
            If fuente.ShowDialog = System.Windows.Forms.DialogResult.OK Then
                RichTextBox1.Font = fuente.Font
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error al cambiar fuente", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try
    End Sub

    Private Sub FondoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ColorFondo.Click
        Dim fondo As New ColorDialog
        fondo.Color = RichTextBox1.BackColor
        If fondo.ShowDialog(Me) = Windows.Forms.DialogResult.OK Then
            Try
                RichTextBox1.BackColor = fondo.Color
            Catch ex As Exception
                MessageBox.Show(ex.Message, "Error al cambiar color", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End Try
        End If
    End Sub

    Private Sub btnGuardar_Click(sender As Object, e As EventArgs) Handles btnGuardar.Click
        Try
            If rutaArchivo <> "" Then
                RichTextBox1.SaveFile(rutaArchivo, RichTextBoxStreamType.PlainText)
                MessageBox.Show("Guardado con éxtio", "Archivo Guardado", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Else
                Dim saveFile1 As New SaveFileDialog()
                saveFile1.DefaultExt = "*.rtf"
                saveFile1.Filter = "Text Files|*.txt"
                If (saveFile1.ShowDialog() = System.Windows.Forms.DialogResult.OK) _
                    And (saveFile1.FileName.Length) > 0 Then
                    RichTextBox1.SaveFile(saveFile1.FileName, RichTextBoxStreamType.PlainText)
                    rutaArchivo = saveFile1.FileName
                    MessageBox.Show("Guardado con éxito", "Archivo Guardado", MessageBoxButtons.OK, MessageBoxIcon.Information)
                End If
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error al guardar archivo", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try

    End Sub

    Private Sub LeemeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LeemeToolStripMenuItem.Click
        Dim loPSI As New ProcessStartInfo
        Dim loProceso As New Process
        loPSI.FileName = "Ayuda.pdf"
        Try
            loProceso = Process.Start(loPSI)
        Catch Ex As Exception
            MessageBox.Show(Ex.Message, "Error al abrir ayuda", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try
    End Sub


    Private Sub ScannerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ScannerToolStripMenuItem.Click
        Dim ventanaComp As New Form2
        ventanaComp.rutaCodigoFuente = rutaArchivo
        ventanaComp.ShowDialog()
    End Sub

    Private Sub ParametrosToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ParametrosToolStripMenuItem.Click
        Dim ventanaParametros As New Parametros
        ventanaParametros.ShowDialog(Me)
    End Sub

    Private Sub CopiarTexto_Click(sender As Object, e As EventArgs) Handles CopiarTexto.Click
        RichTextBox1.Copy()
    End Sub

    Private Sub PictureBox1_Paint(sender As Object, e As PaintEventArgs) Handles PictureBox1.Paint
        Numero = 0

        Dim Altura As Integer = RichTextBox1.GetPositionFromCharIndex(0).Y

        If RichTextBox1.Lines.Length > 0 Then
            For i = 0 To RichTextBox1.Lines.Length - 1
                e.Graphics.DrawString(i + 1, RichTextBox1.Font, Brushes.Red, PictureBox1.Width - (e.Graphics.MeasureString(i + 1, RichTextBox1.Font).Width + 10), Altura)
                Numero += RichTextBox1.Lines(i).Length + 1
                Altura = RichTextBox1.GetPositionFromCharIndex(Numero).Y
            Next
        Else
            e.Graphics.DrawString(1, RichTextBox1.Font, Brushes.Red, PictureBox1.Width - (e.Graphics.MeasureString(1, RichTextBox1.Font).Width + 10), Altura)
        End If
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        PictureBox1.Refresh()
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Interval = 10
        Timer1.Start()

        DataGridView1.Hide()
    End Sub

    Private Sub RichTextBox1_TextChanged(sender As Object, e As EventArgs) Handles RichTextBox1.TextChanged
      

        Dim posicion As Integer

        posicion = RichTextBox1.SelectionStart
        ' MessageBox.Show(posicion.ToString)
        DataGridView1.Hide()
        DataGridView1.ClearSelection()
        'posicion = Cursor.
        Try
            LockWindowUpdate(RichTextBox1.Handle.ToInt32)

            RichTextBox1.SelectionStart = 0
            RichTextBox1.SelectionLength = RichTextBox1.TextLength
            If (active_color = True) Then
                RichTextBox1.SelectionColor = RichTextBox1.ForeColor
                For Each Clave In Claves
                    Dim Index As Integer = 0

                    While Index <= RichTextBox1.Text.LastIndexOf(Clave)
                        RichTextBox1.Find(Clave, Index, RichTextBox1.TextLength, RichTextBoxFinds.MatchCase)
                        RichTextBox1.SelectionColor = Color.Blue
                        Index = RichTextBox1.Text.IndexOf(Clave, Index) + 1
                    End While

                Next

                RichTextBox1.SelectionStart = RichTextBox1.TextLength
                RichTextBox1.SelectionColor = RichTextBox1.ForeColor
            End If
            active_color = True
            LockWindowUpdate(0)
            RichTextBox1.SelectionStart = (posicion)
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try
    End Sub

    Private Sub ScannerParserToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ScannerParserToolStripMenuItem.Click
        Dim p As New Process
        'Dim salida As String

        If (File.Exists("errores.txt")) Then
            p.StartInfo.UseShellExecute = False
            p.StartInfo.RedirectStandardOutput = True
            p.StartInfo.RedirectStandardError = True
            p.StartInfo.FileName = "parser.exe"
            p.StartInfo.Arguments = Chr(34) + rutaArchivo
            p.Start()
            'salida = p.StandardOutput.ReadToEnd        
            p.WaitForExit()
            'Cargar resultados de archivo de texto del scanner, parser

            DataGridView1.Rows.Clear()
            DataGridView1.Show()
            Try
                Dim leer As New StreamReader(Path.GetFullPath("errores.txt"))
                Dim texto As String = ""
                Dim count As Integer = 5
                Dim split As String() = Nothing
                While (Not texto Is Nothing)
                    texto = leer.ReadLine()
                    If (Not texto Is Nothing) Then
                        active_color = False
                        split = texto.Split(New Char() {","}, count)
                        DataGridView1.Rows.Add(split(0), split(1), split(2), split(3))
                    Else
                        MessageBox.Show("Compilación exitosa!!", "Compilación exitosa", MessageBoxButtons.OK, MessageBoxIcon.Information)
                    End If
                End While
                leer.Close()
            Catch ex As Exception
                MsgBox(ex.Message)
            End Try
        Else
            'No existe archivo
            MessageBox.Show("No se pudo obtener infomarción de la compilación", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End If


    End Sub

    Private Sub DataGridView1_CellClick(sender As Object, e As DataGridViewCellEventArgs) Handles DataGridView1.CellClick
        Dim current As Integer = DataGridView1.CurrentRow.Index
        Try
            If DataGridView1.Item(0, current).Value <> "" Then

                Dim selec As String = DataGridView1.CurrentCell.Value
                SelectLine(RichTextBox1, Val(selec))
                RichTextBox1.SelectionColor = Color.Yellow
                'MessageBox.Show("marca")
                RichTextBox1.DeselectAll()
            End If
        Catch ex As Exception
            MessageBox.Show("La linea que desea seleccionarse está en blanco o no existe", "Error", MessageBoxButtons.OK, MessageBoxIcon.Asterisk)
        End Try

    End Sub

    Public Sub SelectLine(ByVal RichTextBox As RichTextBox, _
          ByVal LineNumber As Integer, _
          Optional ByVal FirstLineNumberIsZero _
          As Boolean = False)

        If FirstLineNumberIsZero = False Then
            LineNumber = LineNumber - 1
        End If

        If LineNumber < 0 Then Exit Sub
        If LineNumber > RichTextBox.Lines.Count Then Exit Sub

        RichTextBox.HideSelection = False

        Dim Start As Integer = RichTextBox.GetFirstCharIndexFromLine(LineNumber)
        Dim length As Integer = RichTextBox.Lines(LineNumber).Length
        RichTextBox.SelectionStart = Start
        RichTextBox.SelectionLength = length
        ''RichTextBox1.SelectionStart = 0
        'RichTextBox1.SelectionLength = RichTextBox1.TextLength
        'RichTextBox1.SelectionColor = RichTextBox1.ForeColor
    End Sub

End Class
