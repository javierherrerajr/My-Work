import React from "react";

interface ButtonProps extends React.ButtonHTMLAttributes<HTMLButtonElement> {
  variant?: "default" | "outline";
}

export const Button: React.FC<ButtonProps> = ({
  children,
  variant = "default",
  className = "",
  ...props
}) => {
  const baseClasses = "w-[128px] h-[30px] rounded-[28px] font-baloo2 font-semibold focus:outline-none px-0 py-0";
  const variantClasses =
    variant === "outline"
      ? "border border-gray-300 hover:bg-gray-50"
      : "bg-blue-600 text-white hover:bg-blue-700";

  return (
    <button
      className={`${baseClasses} ${variantClasses} ${className}`}
      {...props}
    >
      {children}
    </button>
  );
};
