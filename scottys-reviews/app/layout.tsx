// app/layout.tsx
import "@/styles/globals.css";
import { ReactNode } from "react";
import { Metadata } from "next";
import { AuthProvider } from "@/app/auth-provider";

export const metadata: Metadata = {
  title: "UCR Course Review",
  description: "Search and review UCR classes with community insights.",
};

export default function RootLayout({ children }: { children: ReactNode }) {
  return (
    <html lang="en">
      <head>
        <link href="https://fonts.googleapis.com/css2?family=Baloo+2&display=swap" rel="stylesheet" />
      </head>
      <body className="min-h-screen bg-[#FFF4E2] text-[#2C1818]">
        <AuthProvider>
          {children}
        </AuthProvider>
      </body>
    </html>
  );
}

