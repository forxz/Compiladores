﻿<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Parametros
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Button1 = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.txtMaxLinea = New System.Windows.Forms.TextBox()
        Me.txtMaxDigit = New System.Windows.Forms.TextBox()
        Me.txtMaxID = New System.Windows.Forms.TextBox()
        Me.txtMaxPal = New System.Windows.Forms.TextBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.SuspendLayout()
        '
        'Button1
        '
        Me.Button1.DialogResult = System.Windows.Forms.DialogResult.OK
        Me.Button1.Location = New System.Drawing.Point(89, 189)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(97, 30)
        Me.Button1.TabIndex = 1
        Me.Button1.Text = "Guardar Cambios"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(30, 27)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(61, 13)
        Me.Label1.TabIndex = 2
        Me.Label1.Text = "MAXLINEA"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(30, 72)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(59, 13)
        Me.Label2.TabIndex = 3
        Me.Label2.Text = "MAXDIGIT"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(0, 0)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(0, 13)
        Me.Label3.TabIndex = 5
        '
        'txtMaxLinea
        '
        Me.txtMaxLinea.Location = New System.Drawing.Point(106, 27)
        Me.txtMaxLinea.Name = "txtMaxLinea"
        Me.txtMaxLinea.Size = New System.Drawing.Size(138, 20)
        Me.txtMaxLinea.TabIndex = 4
        '
        'txtMaxDigit
        '
        Me.txtMaxDigit.Location = New System.Drawing.Point(106, 65)
        Me.txtMaxDigit.Name = "txtMaxDigit"
        Me.txtMaxDigit.Size = New System.Drawing.Size(138, 20)
        Me.txtMaxDigit.TabIndex = 3
        '
        'txtMaxID
        '
        Me.txtMaxID.Location = New System.Drawing.Point(106, 108)
        Me.txtMaxID.Name = "txtMaxID"
        Me.txtMaxID.Size = New System.Drawing.Size(138, 20)
        Me.txtMaxID.TabIndex = 2
        '
        'txtMaxPal
        '
        Me.txtMaxPal.Location = New System.Drawing.Point(106, 150)
        Me.txtMaxPal.Name = "txtMaxPal"
        Me.txtMaxPal.Size = New System.Drawing.Size(138, 20)
        Me.txtMaxPal.TabIndex = 0
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(29, 153)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(71, 13)
        Me.Label4.TabIndex = 6
        Me.Label4.Text = "MAXSTRING"
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(29, 111)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(41, 13)
        Me.Label5.TabIndex = 7
        Me.Label5.Text = "MAXID"
        '
        'Parametros
        '
        Me.ClientSize = New System.Drawing.Size(281, 231)
        Me.Controls.Add(Me.Label5)
        Me.Controls.Add(Me.Label4)
        Me.Controls.Add(Me.txtMaxPal)
        Me.Controls.Add(Me.txtMaxID)
        Me.Controls.Add(Me.txtMaxDigit)
        Me.Controls.Add(Me.txtMaxLinea)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.Button1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "Parametros"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Parámetros"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents txtMaxLinea As System.Windows.Forms.TextBox
    Friend WithEvents txtMaxDigit As System.Windows.Forms.TextBox
    Friend WithEvents txtMaxID As System.Windows.Forms.TextBox
    Friend WithEvents txtMaxPal As System.Windows.Forms.TextBox
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
End Class