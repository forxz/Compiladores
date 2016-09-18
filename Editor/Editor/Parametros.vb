Imports System.IO

Public Class Parametros
    Dim rutaexe$ = ""
    Private Sub Parametros_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Try
            Dim freader As New StreamReader(Path.GetFullPath("param.txt"))
            Dim linea As String ', nombreparam As String, valorparam As String
            Dim datos As New ArrayList()
            
            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(":")(1)
                    Me.txtMaxLinea.Text = linea
                End If

            End If

            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(":")(1)
                    Me.txtMaxDigit.Text = linea
                End If

            End If

            linea = freader.ReadLine()
            If Not linea Is Nothing Then
                If linea.Length <> 0 Then
                    datos.Add(linea)
                    linea = linea.ToString.Split(":")(1)
                    Me.txtMaxID.Text = linea
                End If

            End If
            'Loop Until linea Is Nothing



            freader.Close()

            'For i As Integer = 0 To datos.Count - 1
            '    nombreparam = datos(i).ToString.Split(";")(0)
            '    valorparam = datos(i).ToString.Split(";")(1)
            '    Select Case nombreparam
            '        Case "MAXLINEA"
            'Me.txtMaxLinea.Text = linea
            '        Case "MAXDIGIT"
            'Me.txtMaxDigit.Text = linea
            '        Case "MAXID"
            'Me.txtMaxID.Text = linea
            '        Case "SCNRPATH"
            '            Me.TxtScnrPath.Text = valorparam
            '    End Select
            'Next
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error de lectura", MessageBoxButtons.OK)
        End Try


        'Dim freader As New StreamReader("C:\Users\PC9\Documents\GitHub\Compiladores\Editor\param.txt")
        'Dim contenido As String
        'Dim lineas As New ArrayList()
        'Do
        '    contenido = freader.ReadLine()
        '    If Not contenido Is Nothing Then
        '        'si quiero leer solo las líneas que no estén en blanco incluyo esta condicion
        '        If contenido.Length <> 0 Then
        '            lineas.Add(contenido)
        '            'Me.RichTextBox1.Text = contenido
        '        End If
        '        Me.RichTextBox1.Text = contenido
        '    End If
        'Loop Until contenido Is Nothing
        'freader.Close()
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click

    End Sub
End Class