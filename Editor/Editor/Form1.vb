Imports System.IO
Imports System.Text.RegularExpressions

Public Class Form1
    Dim rutaArchivo$ = ""
    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click, AbrirDoc.Click
        Dim Abrir As New OpenFileDialog()
        Dim STR As System.IO.StreamReader
        Abrir.Filter = "Text(*.txt)|*.txt" 'Tipo de archivo a utilizar
        Abrir.CheckFileExists = True 'Comprueba que el archivo exista
        Abrir.Title = "Abrir documento"
        Abrir.ShowDialog(Me) 'Muestra ventana para seleccionar el archivo a abrir
        Try
            Abrir.OpenFile()
            STR = System.IO.File.OpenText(Abrir.FileName) 'Lee el archivo
            RichTextBox1.Text = STR.ReadToEnd() 'Muestra el contenido del archivo en pantalla
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error al leer archivo", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try
    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click, NuevoDoc.Click
        RichTextBox1.Clear() 'Limpia la pantalla para redactar un nuevo documento
    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click, GuardarDoc.Click
        Dim GuardarComo As New SaveFileDialog()
        Dim STW As System.IO.StreamWriter
        GuardarComo.DefaultExt = "*.rtf" 'Tipo de archivo por defecto a guardar
        GuardarComo.Filter = "Text Files|*.txt" 'Tipo de archivos que se van a guardar
        GuardarComo.CheckPathExists = True 'Revisa si la ruta del archivo existe
        GuardarComo.ShowDialog(Me) 'Muestra un cuadro de dialogo para asignarle nombre al archivo
        Try
            STW = System.IO.File.CreateText(GuardarComo.FileName)
            STW.Write(RichTextBox1.Text)
            STW.Flush()
        Catch ex As Exception

        End Try
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
        'Dim Forma2 As New Form2
        'Forma2.Show()
        Try
            Dim fuente As FontDialog = New FontDialog
            fuente.Font = RichTextBox1.Font
            If fuente.ShowDialog = System.Windows.Forms.DialogResult.OK Then
                RichTextBox1.Font = fuente.Font
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub FondoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ColorFondo.Click
        Dim fondo As New ColorDialog
        fondo.Color = RichTextBox1.BackColor
        fondo.ShowDialog(Me)
        Try
            RichTextBox1.BackColor = fondo.Color
        Catch ex As Exception

        End Try
    End Sub

    Private Sub btnGuardar_Click(sender As Object, e As EventArgs) Handles btnGuardar.Click
        If rutaArchivo <> "" Then
            RichTextBox1.SaveFile(rutaArchivo, RichTextBoxStreamType.PlainText)
        Else
            Dim saveFile1 As New SaveFileDialog()
            saveFile1.DefaultExt = "*.rtf"
            saveFile1.Filter = "Text Files|*.txt"
            If (saveFile1.ShowDialog() = System.Windows.Forms.DialogResult.OK) _
                And (saveFile1.FileName.Length) > 0 Then
                RichTextBox1.SaveFile(saveFile1.FileName, RichTextBoxStreamType.PlainText)
                rutaArchivo = saveFile1.FileName
            End If
        End If
    End Sub

<<<<<<< HEAD
    Private Sub LeemeToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LeemeToolStripMenuItem.Click
        Dim loPSI As New ProcessStartInfo
        Dim loProceso As New Process
        loPSI.FileName = "../Editor/ProyectoCompiladoresParteI.pdf" 'No se porque no abre el pdf
        Try
            loProceso = Process.Start(loPSI)
        Catch Exp As Exception
            MessageBox.Show(Exp.Message, "No se abrio", MessageBoxButtons.OK, MessageBoxIcon.Information)
        End Try
=======
    Private Sub AbrirVentanaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirVentanaToolStripMenuItem.Click
        Dim loPSI As New ProcessStartInfo
        Dim loProceso As New Process
        loPSI.FileName = "Ayuda.pdf"
        Try
            loProceso = Process.Start(loPSI)
        Catch Exp As Exception
        End Try
    End Sub

    Private Sub ToolStripButton14_Click(sender As Object, e As EventArgs) Handles ToolStripButton14.Click
        RichTextBox1.SelectionAlignment = HorizontalAlignment.Left
    End Sub

    Private Sub ToolStripButton15_Click(sender As Object, e As EventArgs) Handles ToolStripButton15.Click
        RichTextBox1.SelectionAlignment = HorizontalAlignment.Center
>>>>>>> origin/Editor
    End Sub

    Private Sub ScannerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ScannerToolStripMenuItem.Click
        Dim ventanaComp As New Form2
        ventanaComp.Show()
    End Sub

    Private Sub ParametrosToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ParametrosToolStripMenuItem.Click
        Dim ventanaParametros As New Parametros
        ventanaParametros.Show()
    End Sub
End Class
