// app/register/layout.tsx

export const metadata = {
    title: "Register | UCR Course Review",
    description: "Create a new account to review and explore UCR classes.",
  };
  
  export default function RegisterLayout({
    children,
  }: {
    children: React.ReactNode;
  }) {
    return <>{children}</>;
  }
  