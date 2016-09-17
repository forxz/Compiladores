Public Class Form1

    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click, AbrirDoc.Click
        Dim Abrir As New OpenFileDialog()
        Dim STR As System.IO.StreamReader
        Abrir.Filter = "Text(*.txt)|*.txt"
        Abrir.CheckFileExists = True
        Abrir.Title = "Abrir documento"
        Abrir.ShowDialog(Me)
        Try
            Abrir.OpenFile()
            STR = System.IO.File.OpenText(Abrir.FileName)
            RichTextBox1.Text = STR.ReadToEnd()
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error al leer archivo", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try
    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click, NuevoDoc.Click
        RichTextBox1.Clear()
    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click, GuardarDoc.Click
        Dim Guardar As New SaveFileDialog()
        Dim STW As System.IO.StreamWriter
        Guardar.Filter = "Text(*.txt)|"
        Guardar.CheckPathExists = True
        Guardar.ShowDialog(Me)
        Try
            STW = System.IO.File.CreateText(Guardar.FileName)
            STW.Write(RichTextBox1.Text)
            STW.Flush()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub ImprimirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ImprimirToolStripMenuItem.Click
        PrintDialog1.ShowDialog()
    End Sub

    Private Sub ToolStripButton4_Click(sender As Object, e As EventArgs) Handles ImpDoc.Click
        PrintDialog1.ShowDialog()
    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Me.Close()
    End Sub

    Private Sub DeshacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DeshacerToolStripMenuItem.Click, Undo.Click
        RichTextBox1.Undo()
    End Sub

    Private Sub RehacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles RehacerToolStripMenuItem.Click, Redo.Click
        RichTextBox1.Redo()
    End Sub

    Private Sub CortarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CortarToolStripMenuItem.Click, CortarTexto.Click
        RichTextBox1.Cut()
    End Sub

    Private Sub CopiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarToolStripMenuItem.Click, CopiarTexto.Click
        RichTextBox1.Copy()
    End Sub

    Private Sub PegarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PegarToolStripMenuItem.Click, PegarTexto.Click
        RichTextBox1.Paste()
    End Sub

    Private Sub SeleccionarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SeleccionarTodoToolStripMenuItem.Click
        RichTextBox1.SelectAll()
    End Sub

    Private Sub LimpiarTexoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles LimpiarTexoToolStripMenuItem.Click
        RichTextBox1.Clear()
    End Sub

    Private Sub FuenteToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FuenteToolStripMenuItem.Click, Fuente.Click
        Try
            Dim fuente As FontDialog = New FontDialog
            fuente.Font = RichTextBox1.Font
            If fuente.ShowDialog = System.Windows.Forms.DialogResult.OK Then
                RichTextBox1.Font = fuente.Font
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub ColorToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ColorToolStripMenuItem.Click, ColorFuente.Click
        Try
            Dim Ncol As ColorDialog = New ColorDialog
            Ncol.Color = RichTextBox1.ForeColor
            If Ncol.ShowDialog = System.Windows.Forms.DialogResult.OK Then
                RichTextBox1.ForeColor = Ncol.Color
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub FondoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles FondoToolStripMenuItem.Click, ColorFondo.Click
        Dim fondo As New ColorDialog
        fondo.Color = RichTextBox1.BackColor
        fondo.ShowDialog(Me)
        Try
            RichTextBox1.BackColor = fondo.Color
        Catch ex As Exception

        End Try
    End Sub

    Private Sub NegritaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NegritaToolStripMenuItem.Click, Negrita.Click
        If RichTextBox1.SelectionFont.Bold Then
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style And Not FontStyle.Bold)
        Else
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style Or FontStyle.Bold)
        End If
        NegritaToolStripMenuItem.Checked = RichTextBox1.SelectionFont.Bold
    End Sub

    Private Sub CursivaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CursivaToolStripMenuItem.Click, Cursiva.Click
        If RichTextBox1.SelectionFont.Italic Then
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style And Not FontStyle.Italic)
        Else
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style Or FontStyle.Italic)
        End If
        CursivaToolStripMenuItem.Checked = RichTextBox1.SelectionFont.Italic
    End Sub

    Private Sub SubrayadoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SubrayadoToolStripMenuItem.Click, SubRaya.Click
        If RichTextBox1.SelectionFont.Underline Then
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style And Not FontStyle.Underline)
        Else
            RichTextBox1.SelectionFont = New Font(RichTextBox1.SelectionFont, RichTextBox1.SelectionFont.Style Or FontStyle.Underline)
        End If
        SubrayadoToolStripMenuItem.Checked = RichTextBox1.SelectionFont.Underline
    End Sub

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
    End Sub

    Private Sub ToolStripButton16_Click(sender As Object, e As EventArgs) Handles ToolStripButton16.Click
        RichTextBox1.SelectionAlignment = HorizontalAlignment.Right
    End Sub

    Private Sub NuevaVentanaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevaVentanaToolStripMenuItem.Click

    End Sub
End Class
